#ifndef GANESHENGINE_GHCONSOLELOGGER_H
#define GANESHENGINE_GHCONSOLELOGGER_H

#include "ghHeaders.h"
#include "ghILogger.h"

namespace ganeshEngine {

class FileLogger : public ILogger {
private:
    int mMaxBulkEntry;
public:
    FileLogger(int maxBulkEntry = 5000) : mMaxBulkEntry(maxBulkEntry) {}
    FileLogger (const FileLogger&) = delete;
    FileLogger& operator=(const FileLogger&) = delete;
    ~FileLogger() {}

    /* TODO Finish and refactor this code */
    void vLog(LOG_LEVEL lvl, const char* file, int line, std::string &message) {
        if(lvl >= m_logLevel) {
            if (currentAmount < MAX_ENTRY - 1) {
                LogEntry *entry = m_stack->alloc<LogEntry>();
                entry->lvl = lvl;
                entry->line = line;
                strcpy(entry->file, file);
                strcpy(entry->message, message.c_str());
                currentEntries->push_front(entry);

                currentAmount++;
            }
            else {
                // open file
                FILE *fp = fopen(m_filename, "a+b");
                if (fp != nullptr) {
                    // write all entries from previous vector in file
                    for (std::list<LogEntry *>::iterator iter = currentEntries->begin();
                         iter != currentEntries->end(); ++iter) {
                        fprintf(
                                fp,
                                "[%7s] %s (%s at line: %d)\n",
                                LOG_LEVELS[(*iter)->lvl].c_str(),
                                (*iter)->message,
                                (*iter)->file,
                                (*iter)->line);
                    }
                    // close file
                    fclose(fp);
                }
                else {
                    _ERROR("Enable to open output log file");
                }
                // switch stack
                m_stack->swapBuffer();
                m_stack->clear();
                // switch vector
                auto temp = pendingEntries;
                pendingEntries = currentEntries;
                currentEntries = temp;

                pendingEntries->clear();

                currentAmount = 0;
                LogEntry *entry = m_stack->alloc<LogEntry>();
                entry->lvl = lvl;
                entry->line = line;
                strcpy(entry->file, file);
                strcpy(entry->message, message.c_str());
                currentEntries->push_back(entry);

                currentAmount++;
            }
        }
    }
};

}

#endif //GANESHENGINE_GHCONSOLELOGGER_H
