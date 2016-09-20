#include "util/ghILogger.hpp"

#include <type_traits>
#include <string>

namespace ganeshEngine {

LOG_CHANNEL operator|(LOG_CHANNEL lhs, LOG_CHANNEL rhs) {
	return (LOG_CHANNEL) (static_cast<_LC>(lhs) | static_cast<_LC>(rhs));
}

LOG_CHANNEL &operator|=(LOG_CHANNEL &lhs, LOG_CHANNEL rhs) {
	lhs = (LOG_CHANNEL) (static_cast<_LC>(lhs) | static_cast<_LC>(rhs));
	return lhs;
}

LOG_CHANNEL operator&(LOG_CHANNEL lhs, LOG_CHANNEL rhs) {
	return (LOG_CHANNEL) (static_cast<_LC>(lhs) & static_cast<_LC>(rhs));
}

LOG_CHANNEL &operator&=(LOG_CHANNEL &lhs, LOG_CHANNEL rhs) {
	lhs = (LOG_CHANNEL) (static_cast<_LC>(lhs) & static_cast<_LC>(rhs));
	return lhs;
}

ILogger::ILogger(LOG_LEVEL logLevel, LOG_CHANNEL logChannel) : mLogLevel(logLevel), mLogChannels(logChannel) {}

bool ILogger::isChannelAllowed(LOG_CHANNEL channels) {
	return ((mLogChannels & channels) == channels);
}

void ILogger::vInitialize(void) {}

void ILogger::vDestroy(void) {}

}