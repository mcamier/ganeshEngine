#include "ghFileLogger.h"

namespace ganeshEngine {

void FileLogger::vLog(LOG_LEVEL lvl, const char* file, int line, std::string &message) {
	if(lvl >= mLogLevel) {
		if (currentAmount < mMaxBulkEntry - 1) {
			appendLogEntry(lvl, file, line, message);
		} else {
			writePendingLogsIntroFileAndSwap();
			appendLogEntry(lvl, file, line, message);
		}
	}
}

void FileLogger::vInitialize(void) {
	FILE *fp = fopen(mFilename, "w");
	fprintf(fp, "");
	fclose(fp);
}

void FileLogger::vDestroy(void) {
	writePendingLogsIntroFileAndSwap();
}

void FileLogger::writePendingLogsIntroFileAndSwap() {
	FILE *fp = fopen(mFilename, "a+b");
	if (fp != nullptr) {
		// write all entries from previous vector in file
		for (std::list<LogEntry *>::iterator iter = mCurrentEntries.begin();
		     iter != mCurrentEntries.end(); ++iter) {
			fprintf(
					fp,
					"[%7s] %35s:%d\t%s\n",
					LOG_LEVELS[(*iter)->lvl].c_str(),
					(*iter)->file,
					(*iter)->line,
					(*iter)->message);
		}
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
}

void FileLogger::appendLogEntry(LOG_LEVEL lvl, const char* file, int line, std::string &message) {
	LogEntry *entry = mDBSAllocator->alloc<LogEntry>();
	entry->lvl = lvl;
	entry->line = line;
	strcpy(entry->file, file);
	strcpy(entry->message, message.c_str());
	mCurrentEntries.push_back(entry);
	currentAmount++;
}

}