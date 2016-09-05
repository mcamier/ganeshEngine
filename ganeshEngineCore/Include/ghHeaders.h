#ifndef GANESHENGINE_GHHEADERS_H
#define GANESHENGINE_GHHEADERS_H

#include <array>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <utility>
#include <tuple>
#include <type_traits>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <list>
#include <array>
#include <chrono>
#include <memory>
#include <stdlib.h>
#include <assert.h>
#include <functional>

#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "ghCore.h"
#include "ghStringId.h"

#ifdef LOGGING_ENABLED
#define _LOG(LOG_LEVEL, MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL, __FILE__, __LINE__, message);\
    }
#define _DEBUG(MESSAGE, CHANNELS) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL::DEBUG, CHANNELS, __FILE__, __LINE__, message);\
    }
#define _WARNING(MESSAGE, CHANNELS) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL::WARNING, CHANNELS, __FILE__, __LINE__, message);\
    }
#define _ERROR(MESSAGE, CHANNELS) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL::ERROR, CHANNELS,__FILE__, __LINE__, message);\
        ASSERT(false);\
    }
#else
#define _LOG(LOG_LEVEL, MESSAGE)
#define _DEBUG(MESSAGE)
#define _WARNING(MESSAGE)
#define _ERROR(MESSAGE)
#endif

#endif //GANESHENGINE_GHHEADERS_H
