#ifndef GANESHENGINE_GHILOGGER_H
#define GANESHENGINE_GHILOGGER_H

#include "ghHeaders.h"

namespace ganeshEngine {

/**
 * Log criticity level
 */
enum LOG_LEVEL {
    TRACE = 0,
    INFO = 1,
    DEBUG = 2,
    WARNING = 3,
    ERROR = 4,
    FATAL = 5
};

/**
 * Log criticity level name
 *
 * @note indexes are related to the LOG_LEVEL enum values
 */
const std::string LOG_LEVELS[] = {
    std::string("TRACE"),
    std::string("INFO"),
    std::string("DEBUG"),
    std::string("WARNING"),
    std::string("ERROR"),
    std::string("FATAL")
};

/**
 * Gather informations about a log
 */
class LogEntry {

public:
	/**
	 * Criticity level of the log
	 */
    LOG_LEVEL lvl;

	/**
	 * Line number which triggered this LogEntry registering
	 */
    int line;

	/**
	 * Filename which triggered this LogEntry registering
	 */
    char file[512];

	/**
	 * Message of the log
	 */
    char message[512];
};


/**
 * Interface for objects providing logging feature
 */
class ILogger {

protected:
	/**
	 * Minimum level needs for a log to be displayed processed by the ILogger instance
	 */
    LOG_LEVEL mLogLevel;

public:
	ILogger(LOG_LEVEL logLevel) : mLogLevel(logLevel) {}
    virtual void vLog(LOG_LEVEL lvl, const char* file, int line, std::string &message) = 0;

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
