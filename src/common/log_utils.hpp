#ifndef RENDERENGINEPLAYGROUND_LOG_UTILS_H
#define RENDERENGINEPLAYGROUND_LOG_UTILS_H

#include <type_traits>
#include <string>

namespace rep
{

/**
 * Log criticity level
 */
enum class LOG_LEVEL : int
{
    DEBUG = 0,
    WARNING = 1,
    ERROR = 2,
    FATAL = 3
};


/**
 *
 */
enum class LOG_CHANNEL : int
{
    DEFAULT = 0x01,
    RENDER = 0x02,
    PHYSICS = 0x04,
    INPUT = 0x08,
    AI = 0x16,
    RESOURCE = 0x32
};
using _LC = std::underlying_type<LOG_CHANNEL>::type;


LOG_CHANNEL operator|(LOG_CHANNEL lhs, LOG_CHANNEL rhs);

LOG_CHANNEL &operator|=(LOG_CHANNEL &lhs, LOG_CHANNEL rhs);

LOG_CHANNEL operator&(LOG_CHANNEL lhs, LOG_CHANNEL rhs);

LOG_CHANNEL &operator&=(LOG_CHANNEL &lhs, LOG_CHANNEL rhs);


/**
 * Log criticity level name
 *
 * @note indexes are related to the LOG_LEVEL enum values
 */
extern const char *LEVEL_NAMES[];


/**
 * Gather informations about a log
 */
struct logEntry_t
{
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

#endif //RENDERENGINEPLAYGROUND_LOG_UTILS_H
