#ifndef GE_LOG_UTILS_H
#define GE_LOG_UTILS_H

#include <type_traits>
#include <string>

namespace ge
{
namespace utils
{

// Log criticity level
typedef enum LogLevelBitsFlag
{
    DEBUG       = 0x01,
    WARNING     = 0x02,
    ERROR       = 0x04,
    FATAL       = 0x08
} LogLevelBitsFlag;
typedef uint8_t LogLevelFlag;


// Log channel
typedef enum LogChannelBitsFlag
{
    DEFAULT     = 0x01,
    RENDER      = 0x02,
    PHYSICS     = 0x04,
    INPUT       = 0x08,
    AI          = 0x10,
    RESOURCE    = 0x20
} LogChannelBitsFlag;
typedef uint8_t LogChannelFlag;


// Log criticity level name
// indexes are related to the LogLevelFlag enum values
static const char *LOG_LEVEL_NAMES[9] = {
        "",
        "DEBUG",        // 0x01
        "WARNING",      // 0x02
        "",
        "ERROR",        // 0x04
        "", "", "",
        "FATAL"         // 0x08
};


// Log channel name
// indexes are related to the LogLevelFlag enum values
static const char *LOG_CHANNEL_NAMES[33] = {
        "",
        "DEFAULT",      // 0x01
        "RENDER",       // 0x02
        "",
        "PHYSICS",      // 0x04
        "","","",
        "INPUT",        // 0x08
        "","","","","","","",
        "AI",           // 0x10
        "","","","","","","","","","","","","","","",
        "RESOURCE"      // 0x20
};


// Gather informations about a log
struct logEntry_t
{
    // Criticity level of the log
    LogLevelFlag lvl;

    //Channel to use for logging this entry
    LogChannelFlag channel;

    // Line number which triggered this LogEntry registering
    uint32_t line;

    // Filename which triggered this LogEntry registering
    char file[512];

    // Message of the log
    char message[512];
};

} //namespace utils
} //namespace ge

#endif //GE_LOG_UTILS_H
