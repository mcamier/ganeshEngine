#include "ghLoggerManager.h"

namespace ganeshEngine {

void LoggerManager::addLogger(ILogger *logger) {
    mLoggers.push_front(logger);
    logger->vInitialize();
}

void LoggerManager::log(LOG_LEVEL lvl, const char* file, int line, std::string &message) {
    for(auto logger : mLoggers) {
        logger->vLog(lvl, file, line, message);
    }
}

void LoggerManager::vInitialize() {
    for(auto logger : mLoggers) {
        logger->vInitialize();
    }
}

void LoggerManager::vDestroy() {
    for(auto logger : mLoggers) {
        logger->vDestroy();
    }
    mLoggers.clear();
}

LoggerManager&(*gLogger)() = &LoggerManager::get;
}