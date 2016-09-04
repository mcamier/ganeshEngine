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
#include "ghResourceManager.h"
#include "ghResourceLoader.h"
#include "ghConfiguration.h"
#include "ghScene.h"

#include "ghStringId.h"

#include "ghMath.h"
#include <glm/glm.hpp>


using namespace std;
using namespace glm;
using namespace ganeshEngine;

class MainScene : public Scene {
private:
    GLProgram program;
    GLTexture *tex{nullptr};
    GLMesh *mesh{nullptr};
    GLMesh *mesh2{nullptr};
    GLModel *model{nullptr};
    GLModel *model2{nullptr};
    Actor *obj{nullptr};

    U64 totalTime = 0;
public:
    MainScene() : Scene() {}

    void vInitialize() override {
        program = GLProgram::create(ShaderType::VERTEX,
                                    "C:/Users/mcamier/ClionProjects/ganeshEngine/ganeshEngineDemo/Resources/vDefault.glsl",
                                    ShaderType::FRAGMENT,
                                    "C:/Users/mcamier/ClionProjects/ganeshEngine/ganeshEngineDemo/Resources/fDefault.glsl");
        tex = new GLTexture();

        unique_ptr<vector<Vertex>> vertices = make_unique<vector<Vertex >>();
        vertices->push_back(Vertex(0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
        vertices->push_back(Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
        vertices->push_back(Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
        mesh = new GLMesh(move(vertices), DrawMode::TRIANGLES);

        unique_ptr<vector<Vertex>> vertices2 = make_unique<vector<Vertex >>();
        vertices2->push_back(Vertex(0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
        vertices2->push_back(Vertex(0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
        vertices2->push_back(Vertex(-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
        mesh2 = new GLMesh(move(vertices2), DrawMode::TRIANGLES);

        model = new GLModel(&program, mesh, tex);
        model->sendToGC();

        model2 = new GLModel(&program, mesh2, tex);
        model2->sendToGC();

        Skybox *root = new Skybox();

        obj = new Actor();
        obj->setModel(model);

        Actor *obj2 = new Actor();
        obj2->setModel(model2);
        obj2->setX(1.0f);

        obj->appendChild(obj2);

        Camera *cam = new Camera(4.0f / 3.0f, 80, 1, 100);
        root->appendChild(cam);
        root->appendChild(obj);
        this->setRoot(root);

        gInput().registerInputCallback<MainScene>(GH_HASH("demoMatchMoveUp"), this, &MainScene::goUp);

        gInput().registerInputCallback<MainScene>(GH_HASH("demoMatchMoveDown"), this, &MainScene::goDown);

        gInput().registerInputCallback<MainScene>(GH_HASH("demoMatchMoveLeft"), this, &MainScene::goLeft);

        gInput().registerInputCallback<MainScene>(GH_HASH("demoMatchMoveRight"), this, &MainScene::goRight);
        gInput().registerInputCallback<MainScene>(GH_HASH("demoMatchReset"), this, &MainScene::reset);
    }

    void update(float deltaTime) override {

    }

    void goUp(RawInput ri, float deltaTime) {
        float move = deltaTime * 1.0f;
        obj->addY(-move);
    }

    void goDown(RawInput ri, float deltaTime) {
        float move = deltaTime * 1.0f;
        obj->addY(move);
    }

    void goRight(RawInput ri, float deltaTime) {
        float move = deltaTime * 1.0f;
        obj->addX(move);
    }

    void goLeft(RawInput ri, float deltaTime) {
        float move = deltaTime * 1.0f;
        obj->addX(-move);
    }

    void reset(RawInput ri, float deltaTime) {
        obj->setX(0.0f);
        obj->setY(0.0f);
    }
};

class MeshObj : public Resource {
};

class MeshObjLoader : public ResourceLoader {
protected:
    unique_ptr<Resource> load(const char *string) const {
        return make_unique<MeshObj>();
    }
};

class ShaderLoader : public ResourceLoader {
protected:
    unique_ptr<Resource> load(const char *string) const {
        return nullptr;
    }
};

int main() {
    Configuration conf;
    LOG_CHANNEL channels = LOG_CHANNEL::RENDER | LOG_CHANNEL::DEFAULT | LOG_CHANNEL::INPUT | LOG_CHANNEL::RESOURCE;

    conf.inputConfigurationFilename = "C:/Users/mcamier/ClionProjects/ganeshEngine/ganeshEngineDemo/Resources/inputConfiguration.json";

    conf.resourceConfigurationFilename = "C:/Users/mcamier/ClionProjects/ganeshEngine/ganeshEngineDemo/Resources/resourceConfiguration.json";

    conf.loggers.push_back(new ConsoleLogger(LOG_LEVEL::DEBUG, LOG_CHANNEL::INPUT));
    conf.loggers.push_back(new FileLogger(LOG_LEVEL::DEBUG, channels, "C:/Users/mcamier/ClionProjects/ganeshEngine/ganeshEngineDemo/Resources/log"));

    conf.customResourceLoaders.insert(make_pair(GH_HASH("MESH_OBJ"), new MeshObjLoader()));
    conf.customResourceLoaders.insert(make_pair(GH_HASH("GL_SHADER"), new ShaderLoader()));

    conf.startScene = new MainScene();

    Application::Initialize(conf);
    /** After application initialization all singletons used by the engine
     *  are created and initialized, so all engine's customization, plugins
     *  addition should take place here, before the start of the main loop
     */
    //gResource().addImporter("shader", new ShaderImporter());
    //gResource().addImporter("meshObj", new ObjResourceLoader());
    //hResource<MeshObj> foobar = gResource().getResource<MeshObj>(GH_HASH("foobar"));
    Application::RunLoop();
    Application::Destroy();
    return 0;
}
