#include "ghConsoleLogger.h"

namespace ganeshEngine {

void ConsoleLogger::vLog(LOG_LEVEL lvl, const char* file, int line, std::string &message) {
	if(lvl >= mLogLevel) {
		fprintf(stdout, "[%7s] %s (%s at line: %d)\n", LOG_LEVELS[lvl].c_str(), message.c_str(), file, line);
	}
}

}