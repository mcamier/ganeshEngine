#ifndef GANESHENGINE_GHILOGGER_H
#define GANESHENGINE_GHILOGGER_H

#include "ghTypes.hpp"
#include "util/ghLog.hpp"

#include <string>
#include <sstream>

#ifdef LOGGING_ENABLED
#define _LOG(LOG_LEVEL, MESSAGE, CHANNELS) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        ganeshEngine::gLog(LOG_LEVEL, CHANNELS, __FILE__, __LINE__, message);\
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
#define _LOG(LOG_LEVEL, MESSAGE, CHANNELS)
#define _DEBUG(MESSAGE, CHANNELS)
#define _WARNING(MESSAGE, CHANNELS)
#define _ERROR(MESSAGE, CHANNELS)
#endif

namespace ganeshEngine {

/**
 * Interface for objects providing logging feature
 */
class ILogger {

protected:
	/**
	 * Minimum level needs for a log to be displayed processed by the ILogger instance
	 */
	LOG_LEVEL mLogLevel;

	LOG_CHANNEL mLogChannels;

public:
	ILogger(LOG_LEVEL logLevel, LOG_CHANNEL logChannel) : mLogLevel(logLevel), mLogChannels(logChannel) {}

	virtual void vLog(LOG_LEVEL lvl, const char *file, int line, std::string &message) = 0;

	/**
	 *
	 * @param channels
	 * @return
	 */
    bool isChannelAllowed(LOG_CHANNEL channels) {
        return ((mLogChannels & channels) == channels);
    }

    /**
     *
     */
    virtual void vFlush() {}

	/**
	 * Initialize logger
	 *
	 * @note Supposed to be called by LoggerManager
	 */
	virtual void vInitialize(void) {}

	/**
	 * Destroy logger
	 *
	 * @note Supposed to be called by LoggerManager
	 */
	virtual void vDestroy(void) {}
};

}

#endif //GANESHENGINE_GHILOGGER_H
