#include "ghFileLogger.h"

namespace ganeshEngine {

/* TODO Finish and refactor this code */
void FileLogger::vLog(LOG_LEVEL lvl, const char* file, int line, std::string &message) {
	if(lvl >= mLogLevel) {
		if (currentAmount < mMaxBulkEntry - 1) {
			LogEntry *entry = mDBSAllocator->alloc<LogEntry>();
			entry->lvl = lvl;
			entry->line = line;
			strcpy(entry->file, file);
			strcpy(entry->message, message.c_str());
			mCurrentEntries.push_front(entry);

			currentAmount++;
		}
		else {
			// open file
			FILE *fp = fopen(mFilename, "a+b");
			if (fp != nullptr) {
				// write all entries from previous vector in file
				for (std::list<LogEntry *>::iterator iter = mCurrentEntries.begin();
				     iter != mCurrentEntries.end(); ++iter) {
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
			mDBSAllocator->swapBuffer();
			mDBSAllocator->clear();
			// switch vector
			auto temp = mPendingEntries;
			mPendingEntries = mCurrentEntries;
			mCurrentEntries = temp;

			mPendingEntries.clear();

			currentAmount = 0;
			LogEntry *entry = mDBSAllocator->alloc<LogEntry>();
			entry->lvl = lvl;
			entry->line = line;
			strcpy(entry->file, file);
			strcpy(entry->message, message.c_str());
			mCurrentEntries.push_back(entry);

			currentAmount++;
		}
	}
}

void FileLogger::vDestroy(void) {
	// TODO append to the log file the last pending log entries
}

}