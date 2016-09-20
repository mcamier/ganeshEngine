#include <ecs/ghActor.hpp>
#include <ecs/ghSceneComponent.hpp>

using namespace std;

namespace ganeshEngine {

RTTI_ABSTRACT_IMPL(Actor, GameObject)

Actor::Actor() :
	GameObject(gGetNextId()),
	mOwnerWorld(nullptr),
	mOwnedComponents(vector<Component*>()),
	mbIgnoredOnSave(true) {}

Actor::Actor(bool ignoredOnSave) :
	GameObject(gGetNextId()),
	mOwnerWorld(nullptr),
	mOwnedComponents(vector<Component*>()),
	mbIgnoredOnSave(ignoredOnSave) {}

Actor::Actor(U32 id) :
	GameObject(id),
	mOwnerWorld(nullptr),
	mOwnedComponents(vector<Component*>()),
	mbIgnoredOnSave(true) {}

Actor::Actor(U32 id, bool ignoredOnSave) :
	GameObject(id),
	mOwnerWorld(nullptr),
	mOwnedComponents(vector<Component*>()),
	mbIgnoredOnSave(ignoredOnSave) {}


void Actor::update(const Clock &clock) {
	//mpRootComponent->update(clock);
}

void Actor::registerComponent(Component* component) {
	if (component == nullptr) return;

	// the component doesn't belongs to anyone at this time in order to be registered
	if( component->mOwnerActor != nullptr ||
		component->mOwnerWorld != nullptr) return;

	if(mpRootComponent != nullptr) {
		// if root present, try to add component to it as sub component
		if(!mpRootComponent->rtti.isDerivedFrom(SceneComponent::rtti)) return;

		((SceneComponent*)mpRootComponent)->registerSubComponent(component);
	} else {
		// if no root already specified, set it the provided component
		mpRootComponent = component;
	}

	// add the component in the list of owned components
	mOwnedComponents.push_back(component);

	// if the actor is already bound in a world, then register the component to it immediatly
	if(mOwnerWorld != nullptr) {
		mOwnerWorld->_registerComponent(component);
	}

	component->mOwnerActor = this;
}

void Actor::registerSubComponent(U32 parentComponentId, Component* subcomponent) {
	if (subcomponent == nullptr) return;

	if( subcomponent->mOwnerActor != nullptr ||
		subcomponent->mOwnerWorld != nullptr) return;

	for(Component* component : mOwnedComponents) {
		if(component->getUID() == parentComponentId) {
			if(component->rtti.isDerivedFrom(SceneComponent::rtti)) {

			}
			else {
				return;
			}
		}
	}
}

bool Actor::isIgnoredOnSave() {
	return mbIgnoredOnSave;
}

void Actor::setIgnoredOnSave(bool newValue) {
	mbIgnoredOnSave = newValue;
}

bool Actor::write(IStream &stream) const {
	return false;
}

bool Actor::read(IStream &stream) {
	return false;
}

}