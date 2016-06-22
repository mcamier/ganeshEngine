#include <iostream>
#include "ghCore.h"
#include "ghApplication.h"
#include "ghLoggerManager.h"
#include "ghFileLogger.h"
#include "ghConsoleLogger.h"
#include "ghHeaders.h"

using namespace std;
using namespace ganeshEngine;


int main() {
	LoggerManager::Initialize();
	gLogger().addLogger(new ConsoleLogger(LOG_LEVEL::TRACE));
	gLogger().addLogger(new FileLogger(LOG_LEVEL::TRACE, "/home/mcamier/workspaces/ganeshEngine/ganeshEngineDemo/error.log"));

	Application::Initialize();
	/** After application initialization all singletons used by the engine
	 *  are created and initialized, so all engine's customization, plugins
	 *  addition should take place here, before the start of the main loop
	 */
	Application::RunLoop();
	Application::Destroy();
    return 0;
}
