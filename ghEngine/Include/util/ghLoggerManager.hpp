#ifndef GANESHENGINE_GHLOGGERMANAGER_H
#define GANESHENGINE_GHLOGGERMANAGER_H

#include "ghHeaders.hpp"
#include "ghSystem.hpp"
#include "ghILogger.hpp"

namespace ganeshEngine {

    using namespace std;

/**
 * Logger Manager can manage one or more ILogger
 *
 * @note for instance you could register both ConsoleLogger and FileLogger at the same time
 */
    class LoggerManager : public System<LoggerManager> {
        friend class System<LoggerManager>;

    private:
        /**
         * List of registered loggers
         *
         * @todo replace raw pointer with std::unique_ptr<ILogger>
         */
        vector<ILogger*> mLoggers;

        LoggerManager() {}

    public:
        LoggerManager(const LoggerManager &) = delete;

        LoggerManager &operator=(const LoggerManager &) = delete;

        ~LoggerManager() {}

        /**
         * Register a new logger
         *
         * @todo replace raw pointer with std::unique_ptr<ILogger>
         */
        void addLogger(ILogger* logger);

        /**
         * Dispatch a log among all the managed loggers
         *
         * @param lvl log level of the given message
         * @param file origin file where comes the log from
         * @param line line of code where comes the log from
         * @param message message to log
         */
        void log(LOG_LEVEL lvl, LOG_CHANNEL logChannel, const char *file, int line, std::string &message);

    protected:
        /**
         * @note Supposed to initialize default loggers, but there is no default ones
         */
        void vInitialize() override;

        /**
         * Release all the managed loggers
         */
        void vDestroy() override;
    };

/**
 * Global getter of reference to the LoggerManager
 * @return
 */
    extern LoggerManager &(*gLogger)();
}

#endif //GANESHENGINE_GHLOGGERMANAGER_H
