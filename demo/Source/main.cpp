#include <iostream>
#include <ecs/ghBoxColliderComponent.hpp>

#include <ghApplication.hpp>
#include <util/ghFileLogger.hpp>
#include <util/ghConsoleLogger.hpp>

#include "defs.hpp"
#include "TeapotActor.hpp"

using namespace std;
using namespace ganeshEngine;


int main() {
    Configuration conf;
    LOG_CHANNEL channels = LOG_CHANNEL::DEFAULT | LOG_CHANNEL::RESOURCE | LOG_CHANNEL::INPUT;

    conf.inputConfigurationFilename = "C:/Users/mcamier/ClionProjects/ganeshEngine/demo/Resources/inputConfiguration.json";

    conf.resourceConfigurationFilename = "C:/Users/mcamier/ClionProjects/ganeshEngine/demo/Resources/resourceConfiguration.json";

    conf.loggers.push_back(new ConsoleLogger(LOG_LEVEL::DEBUG, channels));
    conf.loggers.push_back(new FileLogger(LOG_LEVEL::DEBUG, channels, "C:/Users/mcamier/ClionProjects/ganeshEngine/demo/Resources/log"));

    Application::Initialize(conf);
    /** After application initialization all singletons used by the engine
     *  are created and initialized, so all engine's customization, plugins
     *  addition should take place here, before the start of the main loop
     */
    gWorld().spawnActor(TeapotActor::rtti);

    Application::RunLoop();
    Application::Destroy();
    return 0;
}
