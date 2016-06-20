#include <ghSystem.h>

#include <time.h>
#include <ghPlatform.h>

#include "ghApplication.h"
#include "ghProfilerManager.h"
#include "ghSimulation.h"
#include "ghLoggerManager.h"
#include "ghGLRendererManager.h"

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
    high_resolution_clock::duration elapsedLastFrame {0};

    while(!mIsExiting) {
        currentTime = high_resolution_clock::now();
        elapsedLastFrame = currentTime - lastTime;
        /** For debug purpose if a frame last longer than 0.25 second then the frame
         *  duration will stay 0.25 second, allowing to catch breakpoint without blowing
         *  the game logic with huge frame duration
         */
        if(elapsedLastFrame.count() > 250000000){
            elapsedLastFrame = high_resolution_clock::duration{250000000};
        }
        lastTime = currentTime;
        accumulator += elapsedLastFrame.count();

        while(accumulator >= dt) {
            PROFILE("simulation", gSimulation().tick(dt));

            mMainScene.getRoot()->addY( (F32)((2.0f * cos(totalTime)) * 0.005f));

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
    ProfilerManager::Initialize();
    RendererManager::Initialize();
    Simulation::Initialize();

    _TRACE("CPU : ");
    _TRACE("\t " << Platform::getCpuCoreAmount() << " cores");



    program = GLProgram::create(ShaderType::VERTEX, "/home/mcamier/Workspace/ganeshEngine/ganeshEngineDemo/Resources/vDefault.glsl", ShaderType::FRAGMENT, "/home/mcamier/Workspace/ganeshEngine/ganeshEngineDemo/Resources/fDefault.glsl");
    tex = new GLTexture();

    unique_ptr<vector<Vertex>> vertices = make_unique<vector<Vertex>>();
    vertices->push_back(Vertex(0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
    vertices->push_back(Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
    vertices->push_back(Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
    mesh = new GLMesh(move(vertices), DrawMode::TRIANGLES);

    unique_ptr<vector<Vertex>> vertices2 = make_unique<vector<Vertex>>();
    vertices2->push_back(Vertex(0.0f, 0.5f, 0.0f, 0.5f,0.5f,0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
    vertices2->push_back(Vertex(0.5f, -0.5f, 0.0f, 0.5f,0.5f,0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
    vertices2->push_back(Vertex(-0.5f, -0.5f, 0.0f, 0.5f,0.5f,0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
    mesh2 = new GLMesh(move(vertices2), DrawMode::TRIANGLES);

    model = new GLModel(&program, mesh, tex);
    model->sendToGC();

    model2 = new GLModel(&program, mesh2, tex);
    model2->sendToGC();

    obj = new SceneObject();
    obj->setModel(model);

    SceneObject *obj2 = new SceneObject();
    obj2->setModel(model2);
    obj2->setX(1.0f);

    obj->appendChild(*obj2);
    mMainScene.setRoot(obj);
}

void Application::vDestroy() {
    Simulation::Destroy();
    RendererManager::Destroy();
    ProfilerManager::Destroy();
    LoggerManager::Destroy();
}

void Application::shutdown() {
    mIsExiting = true;
}

Application&(*gApp)() = &Application::get;

}