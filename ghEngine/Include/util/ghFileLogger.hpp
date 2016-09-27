#ifndef GANESHENGINE_GHFILELOGGER_H
#define GANESHENGINE_GHFILELOGGER_H

#include "ghHeaders.hpp"
#include <util/ghILogger.hpp>
#include "../memory/ghDoubleBufferedStackAllocator.hpp"

namespace ganeshEngine {

    using namespace std;


/**
 * More advanced ILogger used to write runtime logs into file in order to be read
 * after the end of the game execution
 *
 * @todo add log channels (like rendering, simulation, events, ...)
 */
    class FileLogger : public ILogger {

    private:
        /** Max amount of LogEntry stored in memory before being written in the log file */
        int mMaxBulkEntry;

        /** Current amount of LogEntry stored in memory before being written in the log file */
        int mCurrentAmount;

        /** Target logging filename */
        const char *mFilename;

        /** Storage for LogEntry s
         * DoubleBufferedStackAllocator is used to separate LogEntry to write at a time and those that will wait until
         * next file writing
         */
        DoubleBufferedStackAllocator *mDBSAllocator;

        /** List of LogEntry s that are written or has been written */
        list<LogEntry *> mCurrentEntries;

        /** List of LogEntry s that will be written later */
        list<LogEntry *> mPendingEntries;

    public:
        FileLogger(LOG_LEVEL logLvl, LOG_CHANNEL logChannel, const char *filename, int maxBulkEntry = 5000) :
                ILogger(logLvl, logChannel),
                mMaxBulkEntry(maxBulkEntry),
                mCurrentAmount(0),
                mFilename(filename) {

            mDBSAllocator = new DoubleBufferedStackAllocator(mMaxBulkEntry * sizeof(LogEntry));
            mDBSAllocator->initialize();
            mCurrentEntries = list<LogEntry *>();
            mPendingEntries = list<LogEntry *>();
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
        void vLog(LOG_LEVEL lvl, const char *file, int line, std::string &message) override;

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
        void writePendingLogsIntroFileAndSwap();

        /**
         * Enqueue a LogEntry before being written in the log file
         *
         * @param lvl log level of the given message
         * @param file origin file where comes the log from
         * @param line line of code where comes the log from
         * @param message message to log
         */
        void appendLogEntry(LOG_LEVEL lvl, const char *file, int line, std::string &message);
    };

}

#endif //GANESHENGINE_GHFILELOGGER_H
