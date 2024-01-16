#include <iostream>
#include "Log_reader.h"

int main() {
    std::string logFilePath;
    std::cout << "Enter the log-file path: ";
    std::cin >> logFilePath;

    unsigned short logFilePort;
    std::cout << "Enter the log-file port: ";
    std::cin >> logFilePort;

    LogReader log(logFilePath, logFilePort);
    log.start();

    return 0;
}
