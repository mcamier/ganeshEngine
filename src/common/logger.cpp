#include "logger.hpp"

namespace rep
{

void ConsoleLogger::vLog(LOG_LEVEL lvl, const char *file, int line, std::string &message)
{
    if (lvl >= mLogLevel)
    {
        fprintf(stdout, "[%7s] %35s:%d\t%s\n",
                LEVEL_NAMES[static_cast<int>(lvl)],
                file,
                line,
                message.c_str());
    }
}

void ConsoleLogger::vFlush()
{}


void FileLogger::vLog(LOG_LEVEL lvl, const char *file, int line, std::string &message)
{
    if (lvl >= mLogLevel)
    {
        if (mCurrentAmount < mMaxBulkEntry - 1)
        {
            appendLogEntry(lvl, file, line, message);
        }
        else
        {
            writePendingLogsIntroFileAndSwap();
            appendLogEntry(lvl, file, line, message);
        }
    }
}

void FileLogger::vInitialize(void)
{
    FILE *fp;
    fopen_s(&fp, mFilename, "w");
    if (fp != nullptr)
    {
        fprintf(fp, "FileLogger initialized");
        fclose(fp);
    }
}

void FileLogger::vFlush()
{
    writePendingLogsIntroFileAndSwap();
}

void FileLogger::vDestroy(void)
{
    writePendingLogsIntroFileAndSwap();
}

void FileLogger::writePendingLogsIntroFileAndSwap()
{
    FILE *fp;
    fopen_s(&fp, mFilename, "a+b");
    if (fp != nullptr)
    {
        // write all entries from previous vector in file
        for (std::list<logEntry_t *>::iterator iter = mCurrentEntries.begin();
             iter != mCurrentEntries.end(); ++iter)
        {
            int lvl = static_cast<int>((*iter)->lvl);
            fprintf(
                    fp,
                    "[%7s] %35s:%d\t%s\n",
                    LEVEL_NAMES[lvl],
                    (*iter)->file,
                    (*iter)->line,
                    (*iter)->message);
        }
        fclose(fp);
    }
    else
    {
        throw std::runtime_error("Enable to open output log file");
    }
    // switch stack
    mDBSAllocator->swapBuffer();
    mDBSAllocator->clear();
    // switch vector
    auto temp = mPendingEntries;
    mPendingEntries = mCurrentEntries;
    mCurrentEntries = temp;

    mPendingEntries.clear();
    mCurrentAmount = 0;
}

void FileLogger::appendLogEntry(LOG_LEVEL lvl, const char *file, int line, std::string &message)
{
    logEntry_t *entry = mDBSAllocator->alloc<logEntry_t>();
    entry->lvl = lvl;
    entry->line = line;
    strcpy_s(entry->file, file);
    strcpy_s(entry->message, message.c_str());
    mCurrentEntries.push_back(entry);
    mCurrentAmount++;
}


void LoggerManager::vInit(LoggerManagerInitializeArgs_t args)
{
    if (args.fileLogEnabled)
    {
        this->fileLogger = new FileLogger(args.logLevel,
                                          args.logChannel,
                                          args.fileLogFilename);
    }
    if (args.consoleLogEnabled)
    {
        this->consoleLogger = new ConsoleLogger(args.logLevel,
                                                args.logChannel);
    }
}

void LoggerManager::vUpdate()
{}

void LoggerManager::vDestroy()
{
    if (this->consoleLogger != nullptr)
    {
        this->consoleLogger->vDestroy();
    }
    if (this->fileLogger != nullptr)
    {
        this->fileLogger->vDestroy();
    }
}

void LoggerManager::logInto(ILogger *logger,
                            LOG_LEVEL lvl,
                            LOG_CHANNEL logChannel,
                            const char *file,
                            int line,
                            std::string &message)
{
    int index = 0;
    int indexLastSlash = -1;
    while (file[index] != '\0')
    {
        if (file[index] == '/' || file[index] == '\\')
        {
            indexLastSlash = index;
        }
        index++;
    }
    if (indexLastSlash != -1)
    {
        std::string filename{file};
        if (logger->isChannelAllowed(logChannel))
        {
            logger->vLog(lvl, filename.substr(indexLastSlash + 1).c_str(), line, message);
        }
    }
    else
    {
        if (logger->isChannelAllowed(logChannel))
        {
            logger->vLog(lvl, file, line, message);
        }
    }
}


void LoggerManager::log(LOG_LEVEL lvl,
                        LOG_CHANNEL logChannel,
                        const char *file,
                        int line,
                        std::string &message)
{
    if (this->consoleLogger != nullptr)
    {
        this->logInto(this->consoleLogger, lvl, logChannel, file, line, message);
    }
    if (this->fileLogger != nullptr)
    {
        this->logInto(this->fileLogger, lvl, logChannel, file, line, message);
    }

}

void LoggerManager::flush()
{
    if (this->consoleLogger != nullptr)
    {
        this->consoleLogger->vFlush();
    }
    if (this->fileLogger != nullptr)
    {
        this->fileLogger->vFlush();
    }
}


}
