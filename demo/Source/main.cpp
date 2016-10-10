#include <iostream>
#include <ecs/ghBoxColliderComponent.hpp>

#include <ghApplication.hpp>
#include <util/ghFileLogger.hpp>
#include <util/ghILogger.hpp>
#include <util/ghConsoleLogger.hpp>
#include <input/ghInputManager.hpp>
#include <resource/ghResourceLoaders.hpp>
#include <ecs/ghModelComponent.hpp>

#include <glm/glm.hpp>
#include "TeapotActor.hpp"

using namespace std;
using namespace ganeshEngine;

static stringId GH_DEMO_ACTION_MOVE_UP = gInternString("demoMatchMoveUp");
static stringId GH_DEMO_ACTION_MOVE_DOWN = gInternString("demoMatchMoveDown");
static stringId GH_DEMO_ACTION_MOVE_RIGHT = gInternString("demoMatchMoveRight");
static stringId GH_DEMO_ACTION_MOVE_LEFT = gInternString("demoMatchMoveLeft");
static stringId GH_DEMO_ACTION_RESET = gInternString("demoMatchReset");

static stringId demoResourceMesh = gInternString("foobar");
static stringId demoResourceTexture = gInternString("dirty");
static stringId demoResourceShaderP = gInternString("defaultShaderProgram");
static stringId demoResourceShaderV = gInternString("defaultVertexShader");
static stringId demoResourceShaderF = gInternString("defaultFragmentShader");


/*
        gInput().registerInputCallback<MainScene>(GH_DEMO_ACTION_MOVE_UP, this, &MainScene::goUp);
        gInput().registerInputCallback<MainScene>(GH_DEMO_ACTION_MOVE_DOWN, this, &MainScene::goDown);
        gInput().registerInputCallback<MainScene>(GH_DEMO_ACTION_MOVE_LEFT, this, &MainScene::goLeft);
        gInput().registerInputCallback<MainScene>(GH_DEMO_ACTION_MOVE_RIGHT, this, &MainScene::goRight);
        gInput().registerInputCallback<MainScene>(GH_DEMO_ACTION_RESET, this, &MainScene::reset);

        model = new Model(
                gResource().getResource<ShaderProgram>(demoResourceShaderP),
                gResource().getResource<Mesh>(demoResourceMesh),
                gResource().getResource<Texture>(demoResourceTexture));

        model->sendToGC();


        modelComponent = new ModelComponent(gGetNextId());
        modelComponent->setMesh(gResource().getResource<Mesh>(demoResourceMesh));
        modelComponent->setShader(gResource().getResource<ShaderProgram>(demoResourceShaderP));
        modelComponent->setTexture(gResource().getResource<Texture>(demoResourceTexture));
        modelComponent->setPosX(1.);
        modelComponent->setPosY(1.);
        modelComponent->setPosZ(1.);

        BoxColliderComponent *collider = new BoxColliderComponent(gGetNextId());
        collider->setPosX(4.);
        collider->setPosY(5.);
        collider->setPosZ(6.);
        //modelComponent->addSubComponent(collider);

        Actor* a = new Actor();
        //a->setRootComponent(modelComponent);
        addActor(a);
*/

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
