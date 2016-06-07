#include "ghLoggerManager.h"

namespace ganeshEngine {

void LoggerManager::addLogger(ILogger *logger) {
    mLoggers.push_front(logger);
}

void LoggerManager::log(LOG_LEVEL lvl, const char* file, int line, std::string &message) {
    for(auto logger : mLoggers) {
        logger->vLog(lvl, file, line, message);
    }
}

void LoggerManager::vInitialize() {}

void LoggerManager::vDestroy() {
    mLoggers.clear();
}

LoggerManager&(*gLogger)() = &LoggerManager::get;
}