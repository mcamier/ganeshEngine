#ifndef GANESHENGINE_GHILOGGER_H
#define GANESHENGINE_GHILOGGER_H

#include <type_traits>
#include <string>

namespace ganeshEngine {

/**
 * Log criticity level
 */
enum LOG_LEVEL {
	DEBUG = 0,
	WARNING = 1,
	ERROR = 2
};

/**
 *
 */
enum class LOG_CHANNEL : int {
	DEFAULT 	= 0x01,
	RENDER 		= 0x02,
	PHYSICS 	= 0x04,
	INPUT 		= 0x08,
	AI 			= 0x16,
	RESOURCE 	= 0x32
};

/**
 * Log criticity level name
 *
 * @note indexes are related to the LOG_LEVEL enum values
 */
const std::string LOG_LEVELS[] = {
	std::string("DEBUG"),
	std::string("WARNING"),
	std::string("ERROR")
};

using _LC = std::underlying_type<LOG_CHANNEL>::type;

inline LOG_CHANNEL operator|(LOG_CHANNEL lhs, LOG_CHANNEL rhs) {
	return (LOG_CHANNEL) (static_cast<_LC>(lhs) | static_cast<_LC>(rhs));
}

inline LOG_CHANNEL &operator|=(LOG_CHANNEL &lhs, LOG_CHANNEL rhs) {
	lhs = (LOG_CHANNEL) (static_cast<_LC>(lhs) | static_cast<_LC>(rhs));
	return lhs;
}

inline LOG_CHANNEL operator&(LOG_CHANNEL lhs, LOG_CHANNEL rhs) {
	return (LOG_CHANNEL) (static_cast<_LC>(lhs) & static_cast<_LC>(rhs));
}

inline LOG_CHANNEL &operator&=(LOG_CHANNEL &lhs, LOG_CHANNEL rhs) {
	lhs = (LOG_CHANNEL) (static_cast<_LC>(lhs) & static_cast<_LC>(rhs));
	return lhs;
}


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
	 * Channel to use for logging this entry
	 */
	LOG_CHANNEL channel;

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
