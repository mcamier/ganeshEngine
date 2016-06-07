#ifndef GANESHENGINE_GHLOGGERMANAGER_H
#define GANESHENGINE_GHLOGGERMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"

namespace ganeshEngine {

using namespace std;

class LoggerManager : public System<LoggerManager>, public ILogger {
    friend class System<LoggerManager>;

private:
    List<ILogger> mLoggers;

public:
    LoggerManager(const LoggerManager&) = delete;
    LoggerManager& operator=(const LoggerManager&) = delete;
    ~LoggerManager() {}

    void addLogger(ILogger* logger);

    void vLog(LOG_LEVEL lvl, const char* file, int line, std::string &message);

protected:
    void vInitialize() override;
    void vDestroy() override;
};

void callLogMgr(LOG_LEVEL logLevel, const char* file, int line, std::string &string);

extern LoggerManager&(*gLogger)();
}

#endif //GANESHENGINE_GHLOGGERMANAGER_H
