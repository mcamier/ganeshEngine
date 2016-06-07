#include <iostream>
#include "ghCore.h"
#include "ghApplication.h"
#include "graphics/ghFrustum.h"
#include "ghLoggerManager.h"
#include "ghFileLogger.h"
#include "ghConsoleLogger.h"

using namespace std;
using namespace ganeshEngine;


int main() {
	Application::Initialize();
	/** After application initialization all singletons used by the engine
	 *  are created and initialized, so all engine's customization, plugins
	 *  addition should take place here, before the start of the main loop
	 */
	gLogger().addLogger(new ConsoleLogger(LOG_LEVEL::DEBUG));
	gLogger().addLogger(new FileLogger(LOG_LEVEL::DEBUG));

	Application::RunLoop();
	Application::Destroy();
    return 0;
}
