#include <iostream>
#include "ghCore.h"
#include <memory>
#include "ghApplication.h"
#include "ghLoggerManager.h"
#include "ghFileLogger.h"
#include "ghConsoleLogger.h"
#include "ghInputManager.h"
#include "ghInputConfiguration.h"
#include "ghPlatform.h"
#include "ghHeaders.h"
#include "ghEvent.h"
#include "ghResource.h"
#include "ghResourceImporter.h"
#include "ghConfiguration.h"

#include "ghMath.h"
#include <glm/glm.hpp>

#include "kzGameplay.h"

using namespace std;
using namespace glm;
using namespace ganeshEngine;

class Dummy{
public:
    int foobar;

    Dummy(int foo) : foobar(foo) {}
};

class ShaderImporter : public ResourceLoader<Dummy> {
protected:
    Dummy* specificLoad(string filename) {
        return new Dummy(666);
    }
};

int main() {
    LOG_CHANNEL channels = LOG_CHANNEL::RENDER | LOG_CHANNEL::DEFAULT | LOG_CHANNEL::INPUT;
    Configuration conf;
    conf.inputConfigurationFilename = "C:/Users/mcamier/ClionProjects/ganeshEngine/ganeshEngineDemo/Resources/inputConfiguration.json";
    conf.resourceConfigurationFilename = "C:/Users/mcamier/ClionProjects/ganeshEngine/ganeshEngineDemo/Resources/resourceConfiguration.json";
    conf.loggers.push_back(new ConsoleLogger(LOG_LEVEL::DEBUG, channels));
    conf.loggers.push_back(new FileLogger(LOG_LEVEL::DEBUG, channels, "C:/Users/mcamier/ClionProjects/ganeshEngine/ganeshEngineDemo/Resources/log"));

    Application::Initialize(conf);
    /** After application initialization all singletons used by the engine
     *  are created and initialized, so all engine's customization, plugins
     *  addition should take place here, before the start of the main loop
     */
    gResource().addImporter("shader", new ShaderImporter());
    auto foobar = gResource().getResource<Dummy>(GH_HASH("defaultVertexShader"));
    auto test = foobar->getRaw();
    Application::RunLoop();
    Application::Destroy();
    return 0;
}
