#ifndef GANESHENGINE_GHLOGGERMANAGER_H
#define GANESHENGINE_GHLOGGERMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"
#include "ghILogger.h"

namespace ganeshEngine {

using namespace std;


class LoggerManager : public System<LoggerManager> {
    friend class System<LoggerManager>;

private:
    list<ILogger*> mLoggers;

public:
    LoggerManager() {}
    LoggerManager(const LoggerManager&) = delete;
    LoggerManager& operator=(const LoggerManager&) = delete;
    ~LoggerManager() {}

    void addLogger(ILogger* logger);

    void log(LOG_LEVEL lvl, const char* file, int line, std::string &message);

protected:
    void vInitialize() override;
    void vDestroy() override;
};


extern LoggerManager&(*gLogger)();
}

#endif //GANESHENGINE_GHLOGGERMANAGER_H
