#include "ecs/ghComponent.hpp"

namespace ganeshEngine {

RTTI_ABSTRACT_IMPL(Component, GameObject)

Component::Component() :
	GameObject(gGetNextId()),
	mOwnerActor(nullptr),
	mParentComponent(nullptr),
	mUpdateEnabled(true) {}

Component::Component(bool updateEnabled) :
	GameObject(gGetNextId()),
	mOwnerActor(nullptr),
	mParentComponent(nullptr),
	mUpdateEnabled(updateEnabled) {}

Component::Component(U32 id) :
	GameObject(id),
	mOwnerActor(nullptr),
	mParentComponent(nullptr),
	mUpdateEnabled(true) {}

Component::Component(U32 id, bool updateEnabled) :
	GameObject(id),
	mOwnerActor(nullptr),
	mParentComponent(nullptr),
	mUpdateEnabled(updateEnabled) {}

void Component::update(const Clock &clock) {
	if (mOwnerWorld != nullptr &&
		mOwnerActor != nullptr &&
		mUpdateEnabled) {
		vUpdate(clock);
	}
}

void Component::activeUpdate() {
	mUpdateEnabled = true;
}

void Component::deactiveUpdate() {
	mUpdateEnabled = false;
}

}
