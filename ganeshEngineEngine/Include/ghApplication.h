#ifndef GANESHENGINE_GHAPPLICATION_H
#define GANESHENGINE_GHAPPLICATION_H

#include "ghHeaders.h"
#include "ghSystem.h"
#include "ghScene.h"
#include "ghClock.h"
#include "ghEvent.h"
#include "ghConfiguration.h"

#include "ghShaderProgram.h"
#include "ghTexture.h"
#include "ghMesh.h"
#include "ghModel.h"

namespace ganeshEngine {

/**
 * Application is the main system in charge of managing all others
 * sub systems, like the logger, the resource manager, the rendering
 * api, etc
 */
class Application : public System<Application> {
	friend class System<Application>;

private:
	/**
	 *
	 */
	Configuration m_configuration;

	/**
	 * By the time the scene is unique and stored directly within the
	 * Application class
	 * Later, game could handle several scenes and they should be
	 * managed by a SceneManager class
	 */
	unique_ptr<Scene> mMainScene;

	/**
	 * The main game clock, will be incremented even if the gameplay
	 * or other sub systems are paused
	 */
	Clock mMainClock;

	/**
	 * Default value is false, assigning true to this variable will
	 * cause to extinction of the game
	 */
	bool mIsExiting = false;

	Application(Configuration conf) : m_configuration(conf) {}

public:
	Application(const Application &) = delete;
	Application &operator=(const Application &) = delete;

	~Application() {}

	/**
	 *  Run the lifecycle of the engine
	 *  It's a static stub used to call the instance's member
	 */
	static void RunLoop();


protected:
	/**
	 * Responsible of the initialization of all subsystems. Basically it will call
	 * the vInitialize method of all sub systems
	 */
	void vInitialize() override;

	/**
	 * Responsible of the destruction of all subsystems. Basically it will call
	 * the vDestroy method of all sub systems
	 */
	void vDestroy() override;

	/**
	 * The main loop logic, to call this method please use the static
	 * stub RunLoop
	 */
	void run();

private:
	/**
	 * Will shutdown the main loop at the next frame iteration
	 */
	void onShutdown(Event *event);
};

/**
 * Global getter of reference to the Application
 * @return reference to the Application
 */
extern Application &(*gApp)();
}


#endif //GANESHENGINE_GHAPPLICATION_H
