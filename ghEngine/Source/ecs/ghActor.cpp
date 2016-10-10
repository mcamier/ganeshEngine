#include <ecs/ghActor.hpp>
#include <ecs/ghSceneComponent.hpp>
#include <util/ghILogger.hpp>

using namespace std;

namespace ganeshEngine {

RTTI_ABSTRACT_IMPL(Actor, GameObject)

Actor::Actor() :
	GameObject(gGetNextId()),
	mOwnedComponents(map<U32, Component*>()),
	mbIgnoredOnSave(true) {}

Actor::Actor(bool ignoredOnSave) :
	GameObject(gGetNextId()),
	mOwnedComponents(map<U32, Component*>()),
	mbIgnoredOnSave(ignoredOnSave) {}

Actor::Actor(U32 id) :
	GameObject(id),
	mOwnedComponents(map<U32, Component*>()),
	mbIgnoredOnSave(true) {}

Actor::Actor(U32 id, bool ignoredOnSave) :
	GameObject(id),
	mOwnedComponents(map<U32, Component*>()),
	mbIgnoredOnSave(ignoredOnSave) {}


void Actor::update(const Clock &clock) {
	//mpRootComponent->update(clock);
}

bool Actor::vInitialize() {
	mpRootComponent = nullptr;
	mOwnedComponents = std::map<U32, Component*>();
	return true;
}

bool Actor::isIgnoredOnSave() {
	return mbIgnoredOnSave;
}

void Actor::setIgnoredOnSave(bool newValue) {
	mbIgnoredOnSave = newValue;
}

bool Actor::addComponent(Component* component, U32 componentParendId) {
	if(component == nullptr) {
		return false;
	}

	if(mpRootComponent == nullptr) {
		mpRootComponent = component;
		mOwnedComponents.insert(make_pair(component->getUID(), component));
	} else {
		auto parentComponentFound = mOwnedComponents.find(componentParendId);

		if(parentComponentFound != mOwnedComponents.end()) {
			Component* parentComponent = parentComponentFound->second;

			if(parentComponent->getRTTI().isDerivedFrom(SceneComponent::rtti)) {
				SceneComponent *psc = static_cast<SceneComponent*>(parentComponent);
				psc->mSubComponents.push_back(component);
				mOwnedComponents.insert(make_pair(component->getUID(), component));
			} else return false;
		} else return false;
	}
	return true;
}

bool Actor::write(IStream &stream) const {
	return false;
}

bool Actor::read(IStream &stream) {
	return false;
}

}