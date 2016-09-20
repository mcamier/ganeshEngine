#include "ghActor.h"

namespace ganeshEngine {

RTTI_DEF(Actor, GameObject)

Actor::Actor() :
	GameObject(gGetNextId()) {}

Actor::Actor(bool ignoredOnSave) :
	GameObject(gGetNextId()),
	mbIgnoredOnSave(ignoredOnSave) {}

Actor::Actor(U32 id) :
	GameObject(id) {}

Actor::Actor(U32 id, bool ignoredOnSave) :
	GameObject(id),
	mbIgnoredOnSave(ignoredOnSave) {}

void Actor::update(const Clock &clock) {
	mpRootComponent->update(clock);
}

void Actor::setRootComponent(Component *root) {
	mpRootComponent = root;
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