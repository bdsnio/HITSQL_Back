#include "log.hpp"
#include <fstream>
#include <time.h>

const void writeToLog(std::string fileName, std::string log) {
    std::fstream logFile;

    logFile.open(fileName.c_str(), std::ios::app);
    if (logFile.is_open()) {
        time_t now = time(0);
        logFile << ctime(&now) << log << std::endl;
        logFile.close();
    }
}