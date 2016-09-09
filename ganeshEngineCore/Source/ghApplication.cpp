#include <ghSystem.h>

#include <time.h>
#include <ghPlatform.h>

#include "ghApplication.h"
#include "ghProfilerManager.h"
#include "ghInputManager.h"
#include "ghLoggerManager.h"
#include "ghResourceManager.h"
#include "ghResourceConfiguration.h"
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
			mMainClock.update(dt);
			PROFILE("input", gInput().vUpdate(mMainClock));
			//PROFILE("scene", mMainScene->update(mMainClock.getLastFrameElapsedTimeAsSecond()));
			PROFILE("event", gEvent().vUpdate(mMainClock));

			accumulator -= dt;
			totalTime += dt;
		}
		//TODO use accumulator to lerp the rendering state
		//PROFILE("rendering", gRenderer().preRender());
		//PROFILE("rendering", gRenderer().render(mMainScene.get()));
		//PROFILE("rendering", gRenderer().postRender());
		gProfiler().update();
	}
}

void Application::vInitialize() {
	mMainClock = Clock(0, 1.0f, false);

	LoggerManager::Initialize();
	for (int i = 0; i < m_configuration.loggers.size(); i++) {
		gLogger().addLogger(m_configuration.loggers[i]);
	}

	EventManager::Initialize();

	Platform::Initialize();

	auto rc = ResourceConfiguration::loadFromFile(m_configuration.resourceConfigurationFilename);
	ResourceManager::Initialize(move(rc), m_configuration.customResourceLoaders);
	gResource().doEagerLoading();

	ProfilerManager::Initialize();

	auto ic = InputManagerConfiguration::loadFromFile(m_configuration.inputConfigurationFilename);
	InputManager::Initialize(ic);

	RendererManager::Initialize();
/*
	mMainScene = unique_ptr<Scene>(m_configuration.startScene);
	mMainScene->vInitialize();*/

	gEvent().addListener<Application>(GH_EVENT_EXIT_GAME, this, &Application::onShutdown);
}

void Application::vDestroy() {
	RendererManager::Destroy();
	InputManager::Destroy();
	ProfilerManager::Destroy();
	ResourceManager::Destroy();
	Platform::Destroy();
	EventManager::Destroy();
	LoggerManager::Destroy();
}

void Application::onShutdown(Event *event) {
	this->mIsExiting = true;
}

Application &(*gApp)() = &Application::get;

}