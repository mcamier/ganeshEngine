#include "log_utils.hpp"

namespace rep
{

const char *LEVEL_NAMES[] = { "DEBUG", "WARNING", "ERROR", "FATAL" };

LOG_CHANNEL operator|(LOG_CHANNEL lhs, LOG_CHANNEL rhs)
{
    return (LOG_CHANNEL) (static_cast<_LC>(lhs) | static_cast<_LC>(rhs));
}

LOG_CHANNEL &operator|=(LOG_CHANNEL &lhs, LOG_CHANNEL rhs)
{
    lhs = (LOG_CHANNEL) (static_cast<_LC>(lhs) | static_cast<_LC>(rhs));
    return lhs;
}

LOG_CHANNEL operator&(LOG_CHANNEL lhs, LOG_CHANNEL rhs)
{
    return (LOG_CHANNEL) (static_cast<_LC>(lhs) & static_cast<_LC>(rhs));
}

LOG_CHANNEL &operator&=(LOG_CHANNEL &lhs, LOG_CHANNEL rhs)
{
    lhs = (LOG_CHANNEL) (static_cast<_LC>(lhs) & static_cast<_LC>(rhs));
    return lhs;
}

}