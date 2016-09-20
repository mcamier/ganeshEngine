#include "ghCore.h"
#include <iostream>
#include "ghLoggerManager.h"

namespace ganeshEngine {

void gLog(LOG_LEVEL logLevel, LOG_CHANNEL logChannels, const char *file, int line, std::string &string) {
    gLogger().log(logLevel, logChannels, file, line, string);
}

}