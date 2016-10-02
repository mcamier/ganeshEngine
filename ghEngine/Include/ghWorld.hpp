#ifndef GANESHENGINE_GHWORLD_H
#define GANESHENGINE_GHWORLD_H

#include "ghSystem.hpp"
#include "util/ghRTTI.hpp"

namespace ganeshEngine {

class Actor;
class Component;

class World : public System<World> {
	friend class System<World>;
	friend class Actor;
	friend class SceneComponent;
	friend class Application;

private:
	map<U32, Actor*> mActors;
	map<U32, Component*> mComponents;

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
	void spawnActor(RTTI* classRTTI);

	/**
	 * Bind a existant actor and its components into the world
	 * @param actor actor to bind
	 */
	void registerActor(Actor* actor);

private:
	/**
	 * Internal purpose
	 *
	 * you cannot directly register component into a world, to do so :
	 * - use World::registerActor to register an Actor and its component
	 * - or use Actor::registerComponent to register a component to an actor
	 *
	 * @param component component to register
	 */
	void _registerComponent(Component* component);


	/**
	 * Internal purpose
	 *
	 * you cannot directly unregister component from a world, to do so :
	 *
	 * @param component component to register
	 */
	void _unregisterComponent(U32 componentId);

protected:
	void vInitialize();

	void vDestroy();

	void vUpdate(const Clock &clock);
};

}

#endif //GANESHENGINE_GHWORLD_H
