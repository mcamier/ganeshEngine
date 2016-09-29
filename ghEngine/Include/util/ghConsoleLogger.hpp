#ifndef GANESHENGINE_GHCONSOLELOGGER_H
#define GANESHENGINE_GHCONSOLELOGGER_H


#include <util/ghILogger.hpp>

namespace ganeshEngine {


/**
 * Basic ILogger forwarding all logs to the stdout
 */
class ConsoleLogger : public ILogger {

public:
    ConsoleLogger(LOG_LEVEL logLvl, LOG_CHANNEL logChannel) : ILogger(logLvl, logChannel) {}

    ConsoleLogger(const ConsoleLogger &) = delete;

    ConsoleLogger &operator=(const ConsoleLogger &) = delete;

    /**
     * Put a log into the stdout
     *
     * @param lvl log level of the given message
     * @param file origin file where comes the log from
     * @param line line of code where comes the log from
     * @param message message to log
     */
    void vLog(LOG_LEVEL lvl, const char *file, int line, std::string &message) override;

    void vFlush() override;
};

}

#endif //GANESHENGINE_GHCONSOLELOGGER_H
