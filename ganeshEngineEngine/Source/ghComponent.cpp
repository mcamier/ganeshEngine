#include "ghComponent.h"

#include "ghActor.h"
#include "ghClock.h"

namespace ganeshEngine {

Component::Component() :
	GameObject(gGetNextId()),
	mUpdateEnabled(true) {}

Component::Component(bool updateEnabled) :
	GameObject(gGetNextId()),
	mUpdateEnabled(updateEnabled) {}

Component::Component(U32 id) :
	GameObject(id),
	mUpdateEnabled(true) {}

Component::Component(U32 id, bool updateEnabled) :
	GameObject(id),
	mUpdateEnabled(updateEnabled) {}

void Component::update(const Clock &clock) {
	if (mUpdateEnabled) {
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
