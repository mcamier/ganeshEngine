#include "ghWorld.hpp"
#include "ecs/ghActor.hpp"
#include "event/ghEventManager.hpp"

namespace ganeshEngine {

World::World() :
	mActors(map<U32, Actor*>()),
	mComponents(map<U32, Component*>()) {}

World::~World() {}

void World::spawnActor(RTTI* classRTTI) {
	if(!classRTTI->isDerivedFrom(Actor::rtti)) return;
}

void World::registerActor(Actor* actor) {
	/* invalid parameter */
	if(actor == nullptr) return;

	/* actor already to a world, try to spawn a new one with the given actor as prototype in order to duplicate it into
	 * this world
	 */
	if(actor->mOwnerWorld != nullptr) return;
	actor->mOwnerWorld = this;

	for(Component* component : actor->mOwnedComponents) {
		_registerComponent(component);
	}
}



void World::_registerComponent(Component* component) {
	if( component->mOwnerActor != nullptr &&
		component->mOwnerWorld == nullptr) {

		mComponents.insert(make_pair(component->getUID(), component));
		component->mOwnerWorld = this;

		//gEvent().queueEvent(new RegisterComponentEvent(component));
	}
}

void World::_unregisterComponent(U32 componentId) {
	auto itr = mComponents.find(componentId);
	Component* component = itr->second;
	mComponents.erase(itr);
	component->mOwnerWorld = nullptr;

	//gEvent().queueEvent(new UnregisterComponentEvent(component));
}

}