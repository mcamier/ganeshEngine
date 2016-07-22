#include "ghLoggerManager.h"

namespace ganeshEngine {

void LoggerManager::addLogger(ILogger *logger) {
    mLoggers.push_front(logger);
    logger->vInitialize();
}

void LoggerManager::log(LOG_LEVEL lvl, LOG_CHANNEL logChannel, const char *file, int line, std::string &message) {
    for (auto logger : mLoggers) {
        int index = 0;
        int indexLastSlash = -1;
        while (file[index] != '\0') {
            if (file[index] == '/' || file[index] == '\\') {
                indexLastSlash = index;
            }
            index++;
        }
        if (indexLastSlash != -1) {
            std::string filename{file};
            if (logger->isChannelAllowed(logChannel)) {
                logger->vLog(lvl, filename.substr(indexLastSlash + 1).c_str(), line, message);
            }
        } else {
            if (logger->isChannelAllowed(logChannel)) {
                logger->vLog(lvl, file, line, message);
            }
        }
    }
}

void LoggerManager::vInitialize() {
    for (auto logger : mLoggers) {
        logger->vInitialize();
    }
}

void LoggerManager::vDestroy() {
    for (auto logger : mLoggers) {
        logger->vDestroy();
    }
    mLoggers.clear();
}

LoggerManager &(*gLogger)() = &LoggerManager::get;
}