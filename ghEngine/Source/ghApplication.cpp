#include "ghApplication.hpp"

#include <time.h>
#include "ghPlatform.hpp"
#include "util/ghProfiler.cpp"
#include "ghSystem.hpp"
#include "util/ghProfilerManager.hpp"
#include "input/ghInputManager.hpp"
#include "util/ghLoggerManager.hpp"
#include "resource/ghResourceManager.hpp"
#include "resource/ghResourceConfiguration.hpp"
#include "render/ghRenderManager.hpp"

#ifdef USE_GLFW_API
#include <window/ghWindowGlfw.hpp>
#endif

#ifdef USE_RENDER_API_GL
#include <render/RenderOpenglAPI.hpp>
#elif USE_RENDER_API_VULKAN
#include <render/RenderVulkanAPI.hpp>
#endif

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
			PROFILE("scene", mMainScene->vUpdate(mMainClock));
			PROFILE("event", gEvent().vUpdate(mMainClock));

			accumulator -= dt;
			totalTime += dt;
		}
		//TODO use accumulator to lerp the rendering state
		//PROFILE("rendering", gRender().preRender());
		//PROFILE("rendering", gRender().window(mMainScene.get()));
		//PROFILE("rendering", gRender().postRender());
		gProfiler().update();
	}
}

void Application::vInitialize() {
	mMainClock = Clock(0, 1.0f, false);

	LoggerManager::Initialize();
	for (U32 i = 0; i < m_configuration.loggers.size(); i++) {
		gLogger().addLogger(m_configuration.loggers[i]);
	};

	auto rc = ResourceConfiguration::loadFromFile(m_configuration.resourceConfigurationFilename);
	auto ic = InputManagerConfiguration::loadFromFile(m_configuration.inputConfigurationFilename);

#ifdef USE_GLFW_API
    mpWindow = new WindowGlfw();
	mpWindow->vInitialize();
#else
    _ERROR("Error during window creation", LOG_CHANNEL::DEFAULT);
    gLogger().flush();
#endif
	EventManager::Initialize();
	Platform::Initialize();
	ResourceManager::Initialize(move(rc), m_configuration.customResourceLoaders);
	//gResource().doEagerLoading();
	ProfilerManager::Initialize();
	InputManager::Initialize(ic);

	mMainScene = unique_ptr<Scene>(m_configuration.startScene);
	mMainScene->vInitialize();
	gEvent().addListener<Application>(GH_EVENT_EXIT_GAME, this, &Application::onShutdown);

#ifdef USE_RENDER_API_GL
	RenderManager::Initialize(new RenderOpenglAPI());
#elif USE_RENDER_API_VULKAN
	RenderManager::Initialize(new RenderVulkanAPI());
#endif
}

void Application::vDestroy() {
#ifdef USE_RENDER_API_GL
	RenderManager::Destroy();
#elif USE_RENDER_API_VULKAN
	RenderManager::Destroy();
#endif
	InputManager::Destroy();
	ProfilerManager::Destroy();
	ResourceManager::Destroy();
	Platform::Destroy();
	EventManager::Destroy();
#ifdef USE_GLFW_API
    mpWindow->vDestroy();
#endif
	LoggerManager::Destroy();
}

void Application::onShutdown(Event *event) {
	this->mIsExiting = true;
}

Application &(*gApp)() = &Application::get;

}