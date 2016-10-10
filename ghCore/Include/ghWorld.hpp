#ifndef GANESHENGINE_GHWORLD_H
#define GANESHENGINE_GHWORLD_H

#include "ghSystem.hpp"
#include "util/ghRTTI.hpp"

#include <vector>

namespace ganeshEngine {

class Actor;
class Component;

class World : public System<World> {
	friend class System<World>;
	friend class Actor;
	friend class SceneComponent;
	friend class Application;

private:
	vector<Actor*> mActorsToInsert;
	map<U32, Actor*> mActors;

	World();

public:
	~World();
	World(const World&) = delete;
	World operator=(const World&) = delete;

	/**
	 * Create an actor of the given type then bind it with its components into the world
	 *
	 * @note Do nothing if the rtti doesn't correspond to an Actor sub class
	 * @param classRTTI class information about the actor to spawn
	 */
	void spawnActor(const RTTI classRTTI);

protected:
	void vInitialize();

	void vDestroy();

	/**
	 * Update every registered actors
	 *
	 * @param clock
	 */
	void vUpdate(const Clock &clock);
};

extern World& (*gWorld)();
}

#endif //GANESHENGINE_GHWORLD_H
