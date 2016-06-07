#ifndef GANESHENGINE_GHCONSOLELOGGER_H
#define GANESHENGINE_GHCONSOLELOGGER_H

#include "ghHeaders.h"
#include "ghILogger.h"

namespace ganeshEngine {

class ConsoleLogger : public ILogger {

public:
    void vLog(LOG_LEVEL lvl, const char* file, int line, std::string &message) {
        if(lvl >= mLogLevel) {
            printf("[%7s] %s (%s at line: %d)\n", LOG_LEVELS[lvl].c_str(), message.c_str(), file, line);
        }
    }
};

}

#endif //GANESHENGINE_GHCONSOLELOGGER_H
