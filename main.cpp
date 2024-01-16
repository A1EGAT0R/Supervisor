#include <iostream>
#include "Log_reader.h"

int main() {
    std::string logFilePath;
    std::cout << "Enter the log-file path: ";
    std::cin >> logFilePath;

    LogReader log(logFilePath, 88);
    log.start();

    return 0;
}
