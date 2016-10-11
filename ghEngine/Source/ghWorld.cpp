#include "ghWorld.hpp"
#include "ecs/ghActor.hpp"
#include "util/ghRTTI.hpp"
#include "event/ghEventManager.hpp"

namespace ganeshEngine {

World::World() :
	mActors(map<U32, Actor*>()) {}

World::~World() {}

void World::spawnActor(const RTTI classRTTI) {
	if(!classRTTI.isDerivedFrom(Actor::rtti)) return;
	Actor* actor = static_cast<Actor*>(RTTIFactory::create(classRTTI));
	mActorsToInsert.push_back(actor);
}

void World::vInitialize() {}

void World::vDestroy() {}

void World::vUpdate(const Clock &clock) {
    // loop over each queued actors in order to add them properly in the world
	for(auto itrInsert = mActorsToInsert.begin() ; itrInsert != mActorsToInsert.end() ; ++itrInsert) {
		bool bActorContainsComponent = false;
        Actor* actor = *itrInsert;

		if(actor->vInitialize()) {
			for(auto compItr = actor->mOwnedComponents.begin(); compItr != actor->mOwnedComponents.end() ; ++compItr) {
		        bActorContainsComponent = true;
				gEvent().queueEvent(new ComponentRegisteredEvent(compItr->second));
			}

            if(bActorContainsComponent) {
			    mActors.insert(make_pair(actor->getUID(), actor));
			    gEvent().queueEvent(new ActorRegisteredEvent());
            }
		}
	}
	mActorsToInsert.clear();

	// finally update all actors
	for(auto itr = mActors.begin() ; itr != mActors.end() ; ++itr) {
		itr->second->update(clock);
	}
}


World& (*gWorld)() = &World::get;

}