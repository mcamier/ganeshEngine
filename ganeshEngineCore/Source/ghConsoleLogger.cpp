#include "ghConsoleLogger.h"

namespace ganeshEngine {

void ConsoleLogger::vLog(LOG_LEVEL lvl, const char* file, int line, std::string &message) {
	if(lvl >= mLogLevel) {
		fprintf(stdout, "[%7s] %35s:%d\t%s\n", LOG_LEVELS[lvl].c_str(), file, line, message.c_str());
	}
}

}