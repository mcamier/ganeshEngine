#include <ghSystem.h>

#include <time.h>
#include <ghPlatform.h>

#include "ghApplication.h"
#include "ghProfilerManager.h"
#include "ghSimulation.h"
#include "ghInputManager.h"
#include "ghLoggerManager.h"
#include "ghResource.h"
#include "ghGLRendererManager.h"
#include "ghSkybox.h"

using namespace std::chrono;

namespace ganeshEngine {

    void Application::RunLoop() {
        Application::get().run();
    }

    void Application::run() {
        U32 dt = 10000000;
        U64 accumulator = 0;
        U64 totalTime = 0;

        high_resolution_clock::time_point lastTime = high_resolution_clock::now();
        high_resolution_clock::time_point currentTime;
        high_resolution_clock::duration elapsedLastFrame{0};

        while (!mIsExiting) {
            currentTime = high_resolution_clock::now();
            elapsedLastFrame = currentTime - lastTime;
            /** For debug purpose if a frame last longer than 0.25 second then the frame
             *  duration will stay 0.25 second, allowing to catch breakpoint without blowing
             *  the game logic with huge frame duration
             */
            if (elapsedLastFrame.count() > 250000000) {
                elapsedLastFrame = high_resolution_clock::duration{250000000};
            }
            lastTime = currentTime;
            accumulator += elapsedLastFrame.count();

            while (accumulator >= dt) {
                PROFILE("input", gInput().update());
                PROFILE("simulation", gSimulation().tick(dt));
                PROFILE("event", gEvent().update());

                obj->addY((F32) ((2.0f * cos(totalTime)) * 0.005f));

                accumulator -= dt;
                totalTime += dt;
            }
            /**
             * TODO : use accumulator to lerp the rendering state
             */
            PROFILE("rendering", gRenderer().preRender());
            PROFILE("rendering", gRenderer().render(mMainScene));
            PROFILE("rendering", gRenderer().postRender());
            gProfiler().update();
        }
    }

    void Application::vInitialize() {
        LoggerManager::Initialize();
        EventManager::Initialize();
        Platform::Initialize();
        ResourceManager::Initialize();
        ProfilerManager::Initialize();
        InputManager::Initialize();
        RendererManager::Initialize();
        Simulation::Initialize();

        auto test = gResource().getResource<Dummy>(1);

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
        mMainScene.setRoot(root);
        //mMainScene.setCamera(shared_ptr<Camera>(cam));
    }

    void Application::vDestroy() {
        Simulation::Destroy();
        RendererManager::Destroy();
        InputManager::Destroy();
        ProfilerManager::Destroy();
        ResourceManager::Destroy();
        Platform::Destroy();
        EventManager::Destroy();
        LoggerManager::Destroy();
    }

    void Application::shutdown() {
        mIsExiting = true;
    }

    Application &(*gApp)() = &Application::get;

}