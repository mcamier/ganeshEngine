#include "logger.hpp"

#include <ctime>

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


void FileLogger::vInitialize(void)
{
    FILE *fp = getLogFile();
    if (fp != nullptr)
    {
        fprintf(fp, "FileLogger initialized");
        fclose(fp);
    }
}

void FileLogger::vDestroy(void)
{
    writePendingLogsIntroFileAndSwap();
}

void FileLogger::vLog(LOG_LEVEL lvl, const char *file, int line, std::string &message)
{
    if (lvl >= mLogLevel)
    {
        if (currentAmount < maxBulkEntry - 1)
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

void FileLogger::vFlush()
{
    writePendingLogsIntroFileAndSwap();
}

void FileLogger::writePendingLogsIntroFileAndSwap()
{
    FILE *fp = getLogFile();
    if (fp != nullptr)
    {
        // write all entries from previous vector in file
        for (std::list<logEntry_t *>::iterator iter = currentEntries.begin();
             iter != currentEntries.end(); ++iter)
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
    pDBSAllocator->swapBuffer();
    pDBSAllocator->clear();
    // switch vector
    auto temp = pendingEntries;
    pendingEntries = currentEntries;
    currentEntries = temp;

    pendingEntries.clear();
    currentAmount = 0;
}

void FileLogger::appendLogEntry(LOG_LEVEL lvl, const char *file, int line, std::string &message)
{
    logEntry_t *entry = pDBSAllocator->alloc<logEntry_t>();
    entry->lvl = lvl;
    entry->line = line;
    strcpy_s(entry->file, file);
    strcpy_s(entry->message, message.c_str());
    currentEntries.push_back(entry);
    currentAmount++;
}

std::string FileLogger::getDateTimeNow()
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%d-%m-%Y_%I-%M-%S", timeinfo);
    std::string dateAsString(buffer);

    return dateAsString;
}

FILE *FileLogger::getLogFile()
{
    FILE *fp;
    std::string dateAsString = this->getDateTimeNow();
    std::string folder(this->folder);
    if(folder.at(folder.size() - 1) != '/') {
        folder = folder.append("/");
    }
    std::string filename = folder.append(baseName)
            .append("-")
            .append(dateAsString)
            .append(".txt");

    fopen_s(&fp, filename.c_str(), "w");
    return fp;
}


void LoggerManager::vInit(LoggerManagerInitializeArgs_t args)
{
    if (args.fileLogEnabled)
    {
        this->pFileLogger = new FileLogger(args.logLevel,
                                           args.logChannel,
                                           args.fileLogFolder,
                                           args.fileLogBaseName);
    }
    if (args.consoleLogEnabled)
    {
        this->pConsoleLogger = new ConsoleLogger(args.logLevel,
                                                 args.logChannel);
    }
}

void LoggerManager::vUpdate()
{}

void LoggerManager::vDestroy()
{
    if (this->pConsoleLogger != nullptr)
    {
        this->pConsoleLogger->vDestroy();
    }
    if (this->pFileLogger != nullptr)
    {
        this->pFileLogger->vDestroy();
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
    if (this->pConsoleLogger != nullptr)
    {
        this->logInto(this->pConsoleLogger, lvl, logChannel, file, line, message);
    }
    if (this->pFileLogger != nullptr)
    {
        this->logInto(this->pFileLogger, lvl, logChannel, file, line, message);
    }

}

void LoggerManager::flush()
{
    if (this->pConsoleLogger != nullptr)
    {
        this->pConsoleLogger->vFlush();
    }
    if (this->pFileLogger != nullptr)
    {
        this->pFileLogger->vFlush();
    }
}


}
