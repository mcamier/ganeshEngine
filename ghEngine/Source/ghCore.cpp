#include "ghCore.hpp"
#include <iostream>
#include "util/ghLoggerManager.hpp"

namespace ganeshEngine {

void gLog(LOG_LEVEL logLevel, LOG_CHANNEL logChannels, const char *file, int line, std::string &string) {
    gLogger().log(logLevel, logChannels, file, line, string);
}

}