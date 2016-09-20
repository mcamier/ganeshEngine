#ifndef GANESHENGINE_GLCORE_H
#define GANESHENGINE_GLCORE_H

#include <string>
#include <cstdio>

#include "ghTypes.hpp"
#include "util/ghILogger.hpp"

namespace ganeshEngine {

/**
 *
 *
 * @param logLevel
 * @param file
 * @param line
 * @param string
 */
void gLog(LOG_LEVEL logLevel, LOG_CHANNEL channels, const char *file, int line, std::string &string);


}
#endif //GANESHENGINE_GLCORE_H
