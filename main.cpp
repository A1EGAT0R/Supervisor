#include <iostream>
#include <vector>
#include "Log_reader.h"

int main() {
    std::string logFilePath;
    std::cout << "Enter the log-file path: ";
    std::cin >> logFilePath;

    unsigned short logFilePort;
    std::cout << "Enter the log-file port: ";
    std::cin >> logFilePort;

    std::cout << "Enter the critical log levels. For end, print #cnt\n";
    std::vector<std::string> critical_value;
    std::string input_values;
    std::cin >> input_values;
    while(input_values!="#cnt")
    {
        critical_value.push_back(input_values);
        std::cin >> input_values;
    }

    LogReader log(logFilePath, logFilePort, critical_value);
    log.start();

    return 0;
}
