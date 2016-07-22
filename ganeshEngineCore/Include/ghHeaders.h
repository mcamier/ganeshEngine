#ifndef GANESHENGINE_GHHEADERS_H
#define GANESHENGINE_GHHEADERS_H

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

#include "ghCore.h"

#ifdef LOGGING_ENABLED
	#define _LOG(LOG_LEVEL, MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL, __FILE__, __LINE__, message);\
    }
	#define _TRACE(MESSAGE, CHANNELS) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL::TRACE, CHANNELS, __FILE__, __LINE__, message);\
    }
	#define _INFO(MESSAGE, CHANNELS) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL::INFO, CHANNELS,__FILE__, __LINE__, message);\
    }
	#define _DEBUG(MESSAGE, CHANNELS) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL::DEBUG, CHANNELS,__FILE__, __LINE__, message);\
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
    }
	#define _FATAL(MESSAGE, CHANNELS) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL::FATAL, CHANNELS,__FILE__, __LINE__, message);\
        gApp().shutdown();\
    }
#else
	#define _LOG(LOG_LEVEL, MESSAGE)
	#define _TRACE(MESSAGE)
	#define _INFO(MESSAGE)
	#define _DEBUG(MESSAGE)
	#define _WARNING(MESSAGE)
	#define _ERROR(MESSAGE)
	#define _FATAL(MESSAGE)
#endif

#endif //GANESHENGINE_GHHEADERS_H
