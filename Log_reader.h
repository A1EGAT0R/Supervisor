#pragma once

#include <boost/asio.hpp>
#include <fstream>
#include <string>
#include<boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <queue>
#include "LogInfo.h"

class LogReader: public boost::enable_shared_from_this<LogReader>
{
private:
    void reading_until_err();
    void asyncSend();
    void sendToServer(const boost::system::error_code&);
    void stopper();

public:
    LogReader(std::string pathToLogFile,  unsigned short serv_port):
                                ep(boost::asio::ip::tcp::v4(), serv_port),
                                sock(io),
                                isWorked(true),
                                readPos(0),
                                acceptor(io, ep)
                                {
                                    this->pathToLogFile = std::move(pathToLogFile);
                                }


    void start();
    ~LogReader(){
        io.run();
        sock.close();
    }

private:
    std::condition_variable newLog;
    std::mutex newLogWaiter;
    boost::asio::io_service io;
    boost::asio::ip::tcp::socket sock;
    boost::asio::ip::tcp::endpoint ep;
    boost::asio::ip::tcp::acceptor acceptor;
    std::ifstream ist;
    std::string pathToLogFile;
    std::queue<std::string> outputLogs;
    int readPos;
    bool isWorked;

};