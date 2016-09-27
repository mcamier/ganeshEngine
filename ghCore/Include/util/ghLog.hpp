#ifndef GANESHENGINE_GHLOG_H
#define GANESHENGINE_GHLOG_H

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
    DEFAULT = 0x01,
    RENDER = 0x02,
    PHYSICS = 0x04,
    INPUT = 0x08,
    AI = 0x16,
    RESOURCE = 0x32
};

typedef std::underlying_type<LOG_CHANNEL>::type _LC;

LOG_CHANNEL operator|(LOG_CHANNEL lhs, LOG_CHANNEL rhs);

LOG_CHANNEL &operator|=(LOG_CHANNEL &lhs, LOG_CHANNEL rhs);

LOG_CHANNEL operator&(LOG_CHANNEL lhs, LOG_CHANNEL rhs);

LOG_CHANNEL &operator&=(LOG_CHANNEL &lhs, LOG_CHANNEL rhs);

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

}

#endif //GANESHENGINE_GHLOG_H
