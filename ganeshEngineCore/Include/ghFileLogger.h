#ifndef GANESHENGINE_GHFILELOGGER_H
#define GANESHENGINE_GHFILELOGGER_H

#include "ghHeaders.h"
#include "ghILogger.h"
#include "ghDoubleBufferedStackAllocator.h"

namespace ganeshEngine {

using namespace std;

class FileLogger : public ILogger {

private:
    int mMaxBulkEntry;
    int currentAmount;
    const char *mFilename;
    DoubleBufferedStackAllocator *mDBSAllocator;
    list<LogEntry*> mCurrentEntries;
    list<LogEntry*> mPendingEntries;

public:
    FileLogger(LOG_LEVEL logLvl, const char* filename, int maxBulkEntry = 5000) :
        mMaxBulkEntry(maxBulkEntry),
        mFilename(filename),
        ILogger(logLvl) {

        mDBSAllocator = new DoubleBufferedStackAllocator(mMaxBulkEntry * sizeof(LogEntry));
        mDBSAllocator->initialize();
        currentAmount = 0;
    }

    FileLogger (const FileLogger&) = delete;
    FileLogger& operator=(const FileLogger&) = delete;

    void vLog(LOG_LEVEL lvl, const char* file, int line, std::string &message) override;

    void vDestroy(void) override;
};

}

#endif //GANESHENGINE_GHFILELOGGER_H
