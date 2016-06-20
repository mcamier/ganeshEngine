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

#include <glm/glm.hpp>

#include "ghCore.h"

#ifdef LOGGING_ENABLED
	#define _LOG(LOG_LEVEL, MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL, __FILE__, __LINE__, message);\
    }
	#define _TRACE(MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL::TRACE, __FILE__, __LINE__, message);\
    }
	#define _INFO(MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL::INFO, __FILE__, __LINE__, message);\
    }
	#define _DEBUG(MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL::DEBUG, __FILE__, __LINE__, message);\
    }
	#define _WARNING(MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL::WARNING, __FILE__, __LINE__, message);\
    }
	#define _ERROR(MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL::ERROR, __FILE__, __LINE__, message);\
    }
	#define _FATAL(MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL::FATAL, __FILE__, __LINE__, message);\
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
