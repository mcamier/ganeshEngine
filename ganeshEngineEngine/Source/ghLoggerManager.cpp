#include "ghLoggerManager.h"

namespace ganeshEngine {

    void LoggerManager::addLogger(ILogger* logger) {
        logger->vInitialize();
        mLoggers.push_back(logger);
    }

    void LoggerManager::log(LOG_LEVEL lvl, LOG_CHANNEL logChannel, const char *file, int line, std::string &message) {
        for (auto itr = mLoggers.begin(); itr != mLoggers.end() ; ++itr) {
            int index = 0;
            int indexLastSlash = -1;
            while (file[index] != '\0') {
                if (file[index] == '/' || file[index] == '\\') {
                    indexLastSlash = index;
                }
                index++;
            }
            if (indexLastSlash != -1) {
                std::string filename{file};
                if ((*itr)->isChannelAllowed(logChannel)) {
                    (*itr)->vLog(lvl, filename.substr(indexLastSlash + 1).c_str(), line, message);
                }
            } else {
                if ((*itr)->isChannelAllowed(logChannel)) {
                    (*itr)->vLog(lvl, file, line, message);
                }
            }
        }
    }

    void LoggerManager::vInitialize() {
        for (auto itr = mLoggers.begin() ; itr != mLoggers.end() ; ++itr) {
            (*itr)->vInitialize();
        }
    }

    void LoggerManager::vDestroy() {
        for (auto itr = mLoggers.begin() ; itr != mLoggers.end() ; ++itr) {
            (*itr)->vDestroy();
        }
        mLoggers.clear();
    }

    LoggerManager &(*gLogger)() = &LoggerManager::get;
}