#include <iostream>
#include "ghCore.h"
#include "ghApplication.h"
#include "ghLoggerManager.h"
#include "ghFileLogger.h"
#include "ghConsoleLogger.h"
#include "ghInputManager.h"
#include "ghInputConfiguration.h"
#include "ghPlatform.h"
#include "ghHeaders.h"
#include "ghEvent.h"


#include "ghMath.h"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;
using namespace ganeshEngine;

/**
 * 
 */

int main()
{
    LoggerManager::Initialize();
    LOG_CHANNEL channels = LOG_CHANNEL::RENDER | LOG_CHANNEL::DEFAULT | LOG_CHANNEL::INPUT;
    gLogger().addLogger(new ConsoleLogger(LOG_LEVEL::DEBUG, LOG_CHANNEL::DEFAULT | LOG_CHANNEL::INPUT));
    gLogger().addLogger(new FileLogger(LOG_LEVEL::DEBUG, channels, "C:/Users/mcamier/ClionProjects/ganeshEngine/ganeshEngineDemo/log"));

    EventManager::Initialize();
    Platform::Initialize();

    auto ic = InputManagerConfiguration::loadFromFile(string("C:/Users/mcamier/ClionProjects/ganeshEngine/ganeshEngineDemo/Resources/inputConfiguration.json"));
    InputManager::Initialize(move(ic));

    Application::Initialize();
    /** After application initialization all singletons used by the engine
     *  are created and initialized, so all engine's customization, plugins
     *  addition should take place here, before the start of the main loop
     */
    Application::RunLoop();
    Application::Destroy();
    return 0;
}
