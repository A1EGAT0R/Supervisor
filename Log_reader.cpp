#include "Log_reader.h"
#include <boost/bind.hpp>
#include <iostream>
const size_t EOF_SLEEP_SEC = 60;

void
LogReader::start()
{
    if(!ist) return;

    asyncSend();
    boost::thread th([&]()
                     {
                        io.run();
                     });
    reading_until_err();
    th.join();
}

void
LogReader::reading_until_err()
{
    while(isWorked) {
        ist.open(pathToLogFile);
        ist.seekg(readPos);
        while (!ist.eof()) {
            std::string read;
            std::getline(ist, read);

            int temp = ist.tellg();
            if(temp>0) readPos = temp;

            LogInfo current_log(read);

            bool is_error = current_log.getError() == LogInfo::string_error_types[LogInfo::ERROR]
                            || current_log.getError() == LogInfo::string_error_types[LogInfo::FATAL];

            if (is_error) {
                outputLogs.push(current_log.getStringFormat());
                newLog.notify_one();
            }

        }
        ist.close();
        boost::this_thread::sleep_for(boost::chrono::seconds(EOF_SLEEP_SEC));
    }
}

void
LogReader::asyncSend()
{
        acceptor.async_accept(sock, [&](const boost::system::error_code& err)
        {
            std::cout << "CONGRAT\n";
            std::unique_lock<std::mutex> u_newLogWaiter(newLogWaiter);
            while(true) {
                while (isWorked) {
                    sendToServer(err);
                    newLog.wait(u_newLogWaiter);
                }
            }

        });
}



void
LogReader::sendToServer(const boost::system::error_code& err)
{
    while(!outputLogs.empty()) {
        sock.async_write_some(boost::asio::buffer(outputLogs.front() + '\n'),
                              [&](const boost::system::error_code &err, std::size_t sz)
                              {
                              });
        outputLogs.pop();
    }

}
