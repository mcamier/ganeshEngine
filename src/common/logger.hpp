#ifndef RENDERENGINEPLAYGROUND_LOGGER_H
#define RENDERENGINEPLAYGROUND_LOGGER_H

#include "managers.hpp"
#include "memory.hpp"
#include "log_utils.hpp"

#include <type_traits>
#include <list>
#include <string>

#ifdef LOGGING_ENABLED
#include <string>
#include <sstream>
#include <stdexcept>
#define REP_LOG(LOG_LEVEL, MESSAGE, CHANNELS) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        LoggerManager::get().log(LOG_LEVEL, CHANNELS, __FILE__, __LINE__, message);\
    }
#define REP_DEBUG(MESSAGE, CHANNELS) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        LoggerManager::get().log(LOG_LEVEL::DEBUG, CHANNELS, __FILE__, __LINE__, message);\
    }
#define REP_WARNING(MESSAGE, CHANNELS) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        LoggerManager::get().log(LOG_LEVEL::WARNING, CHANNELS, __FILE__, __LINE__, message);\
    }
#define REP_ERROR(MESSAGE, CHANNELS) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        LoggerManager::get().log(LOG_LEVEL::ERROR, CHANNELS,__FILE__, __LINE__, message);\
    }
#define REP_FATAL(MESSAGE, CHANNELS) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        LoggerManager::get().log(LOG_LEVEL::FATAL, CHANNELS,__FILE__, __LINE__, message);\
        throw std::runtime_error("Fatal error occured");\
    }
#else
#define REP_LOG(LOG_LEVEL, MESSAGE, CHANNELS)
#define REP_DEBUG(MESSAGE, CHANNELS)
#define REP_WARNING(MESSAGE, CHANNELS)
#define REP_ERROR(MESSAGE, CHANNELS)
#define REP_FATAL(MESSAGE, CHANNELS)
#endif


namespace rep {


struct LoggerManagerInitializeArgs_t
{
    LOG_LEVEL logLevel;
    LOG_CHANNEL logChannel;
    bool consoleLogEnabled;
    bool fileLogEnabled;
    const char * fileLogFolder;
    const char * fileLogBaseName;
};


class ILogger {

protected:
    /**
     * Minimum level needs for a log to be displayed processed by the ILogger instance
     */
    LOG_LEVEL mLogLevel;

    LOG_CHANNEL mLogChannels;

public:
    ILogger(LOG_LEVEL logLevel,
            LOG_CHANNEL logChannel) : mLogLevel(logLevel), mLogChannels(logChannel) {}

    virtual void vLog(LOG_LEVEL lvl,
                      const char *file,
                      int line,
                      std::string &message) = 0;

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


class ConsoleLogger : public ILogger {

public:
    ConsoleLogger(LOG_LEVEL logLvl,
                  LOG_CHANNEL logChannel) : ILogger(logLvl, logChannel) {}

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
    void vLog(LOG_LEVEL lvl,
              const char *file,
              int line,
              std::string &message) override;

    void vFlush() override;
};


class FileLogger : public ILogger {

private:
    /** Max amount of LogEntry stored in memory before being written in the log file */
    int maxBulkEntry;

    /** Current amount of LogEntry stored in memory before being written in the log file */
    int currentAmount;

    /** Target logging folder */
    const char *folder;

    const char *baseName;

    /** Storage for LogEntry s
     * DoubleBufferedStackAllocator is used to separate LogEntry to write at a time and those that will wait until
     * next file writing
     */
    DoubleBufferedStackAllocator *pDBSAllocator;

    /** List of LogEntry s that are written or has been written */
    std::list<logEntry_t *> currentEntries;

    /** List of LogEntry s that will be written later */
    std::list<logEntry_t *> pendingEntries;

public:
    FileLogger(LOG_LEVEL logLvl,
               LOG_CHANNEL logChannel,
               const char *folder,
               const char *baseName,
               int maxBulkEntry = 5000) :
            ILogger(logLvl, logChannel),
            maxBulkEntry(maxBulkEntry),
            currentAmount(0),
            folder(folder),
            baseName(baseName) {

        pDBSAllocator = new DoubleBufferedStackAllocator(maxBulkEntry * sizeof(logEntry_t));
        pDBSAllocator->initialize();
        currentEntries = std::list<logEntry_t *>();
        pendingEntries = std::list<logEntry_t *>();
    }

    FileLogger(const FileLogger &) = delete;

    FileLogger &operator=(const FileLogger &) = delete;

    /**
     * Put a log into the logging file
     *
     * @param lvl log level of the given message
     * @param file origin file where comes the log from
     * @param line line of code where comes the log from
     * @param message message to log
     */
    void vLog(LOG_LEVEL lvl,
              const char *file,
              int line,
              std::string &message) override;

    /**
     *
     */
    void vFlush() override;

    /**
     * Initialize the fileLogging by erasing the content of the logging file if
     * it already exists
     */
    void vInitialize(void) override;

    /**
     * Destroy the FileLogger
     *
     * @note Usualy Loggers are destroyed when the LoggerManager is destroyed on the game
     * extinction, by the way at this time the last pending LogEntry s that are not
     * saved in the file needs to be written : the vDestroy method takes care of that
     */
    void vDestroy(void) override;

private:
    /**
     * Internal helper writting pending LogEntry s into file
     */
    void writePendingLogsIntoFileAndSwap();

    /**
     * Enqueue a LogEntry before being written in the log file
     *
     * @param lvl log level of the given message
     * @param file origin file where comes the log from
     * @param line line of code where comes the log from
     * @param message message to log
     */
    void appendLogEntry(LOG_LEVEL lvl, const char *file, int line, std::string &message);

    FILE * getLogFile();

    std::string getDateTimeNow();
};


class LoggerManager :
        public SingletonManager<LoggerManager, LoggerManagerInitializeArgs_t>
{
    friend SingletonManager<LoggerManager, LoggerManagerInitializeArgs_t>;

private:
    ConsoleLogger *pConsoleLogger;
    FileLogger *pFileLogger;

protected:
    LoggerManager() = default;

    LoggerManager(const LoggerManager &) = delete;

    LoggerManager &operator=(const LoggerManager &) = delete;

    void vInit(LoggerManagerInitializeArgs_t args) override;


    void vDestroy() override;

public:
    void vUpdate() override;
    /**
         * Dispatch a log among all the managed loggers
         *
         * @param lvl log level of the given message
         * @param file origin file where comes the log from
         * @param line line of code where comes the log from
         * @param message message to log
         */
    void log(LOG_LEVEL lvl,
             LOG_CHANNEL logChannel,
             const char *file,
             int line,
             std::string &message);

    /**
     *
     */
    void flush();

private:
    void logInto(ILogger *logger,
                 LOG_LEVEL lvl,
                 LOG_CHANNEL logChannel,
                 const char *file,
                 int line,
                 std::string &message);
};

}


#endif //RENDERENGINEPLAYGROUND_LOGGER_H