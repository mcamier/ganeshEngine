#include <iostream>
#include <ghBoxColliderComponent.h>

#include "ghApplication.h"
#include "ghFileLogger.h"
#include "ghILogger.h"
#include "ghConsoleLogger.h"
#include "ghInputManager.h"
#include "ghResourceLoaders.h"
#include "ghModelComponent.h"

using namespace std;
using namespace glm;
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


class MainScene : public Scene {
private:
    Model *model{nullptr};

    ModelComponent *modelComponent;

public:
    MainScene() : Scene() {}

    void vInitialize() override {
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
/*
        modelComponent->setPosX(1.);
        modelComponent->setPosY(1.);
        modelComponent->setPosZ(1.);

        BoxColliderComponent *collider = new BoxColliderComponent(gGetNextId());
        collider->setPosX(4.);
        collider->setPosY(5.);
        collider->setPosZ(6.);
        //modelComponent->addSubComponent(collider);
*/
        Actor* a = new Actor(gGetNextId());
        //a->setRootComponent(modelComponent);
        addActor(a);

    }

    void vUpdate(const Clock &clock) override {
        Scene::vUpdate(clock);
        //modelComponent->setLocationX(modelComponent->getLocation().x + 1);
    }


    void goUp(RawInput ri, float deltaTime) {}

    void goDown(RawInput ri, float deltaTime) {}

    void goRight(RawInput ri, float deltaTime) {}

    void goLeft(RawInput ri, float deltaTime) {}

    void reset(RawInput ri, float deltaTime) {}

    };

int main() {
    Configuration conf;
    LOG_CHANNEL channels = LOG_CHANNEL::DEFAULT | LOG_CHANNEL::RESOURCE;

    conf.inputConfigurationFilename = "C:/Users/mcamier/ClionProjects/ganeshEngine/demo/Resources/inputConfiguration.json";

    conf.resourceConfigurationFilename = "C:/Users/mcamier/ClionProjects/ganeshEngine/demo/Resources/resourceConfiguration.json";

    conf.loggers.push_back(new ConsoleLogger(LOG_LEVEL::DEBUG, channels));
    conf.loggers.push_back(new FileLogger(LOG_LEVEL::DEBUG, channels, "C:/Users/mcamier/ClionProjects/ganeshEngine/demo/Resources/log"));

    conf.startScene = new MainScene();

    Application::Initialize(conf);
    /** After application initialization all singletons used by the engine
     *  are created and initialized, so all engine's customization, plugins
     *  addition should take place here, before the start of the main loop
     */
    Application::RunLoop();
    Application::Destroy();
    return 0;
}
