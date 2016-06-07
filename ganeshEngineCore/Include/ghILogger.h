#ifndef GANESHENGINE_GHILOGGER_H
#define GANESHENGINE_GHILOGGER_H

#include "ghHeaders.h"

namespace ganeshEngine {

/**
 * enum LOG_LEVEL
 */
enum LOG_LEVEL {
    TRACE = 0,
    INFO = 1,
    DEBUG = 2,
    WARNING = 3,
    ERROR = 4,
    FATAL = 5
};

const std::string LOG_LEVELS[] = {
    std::string("TRACE"),
    std::string("INFO"),
    std::string("DEBUG"),
    std::string("WARNING"),
    std::string("ERROR"),
    std::string("FATAL")
};

/**
 * LogEntry class
 */
class LogEntry {

public:
    LOG_LEVEL lvl;
    int line;
    char file[512];
    char message[512];
};

class ILogger {

    protected:
        LOG_LEVEL mLogLevel;

    public:
        ILogger(LOG_LEVEL logLevel) : mLogLevel(logLevel) {}
        virtual void vLog(LOG_LEVEL lvl, const char* file, int line, std::string &message) = 0;
};

}

#endif //GANESHENGINE_GHILOGGER_H
