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

            accumulator -= dt;
            totalTime += dt;
        }
        /** TODO : use accumulator to lerp the rendering state
         */
        PROFILE("rendering", gRenderer().update());
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