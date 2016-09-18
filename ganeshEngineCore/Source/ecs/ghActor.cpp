#include "ecs/ghActor.h"

namespace ganeshEngine {

RTTI_DEF(Actor, GameObject)

Actor::Actor(U32 id) : GameObject(id) {}

void Actor::update(const Clock& clock) {
    mpRootComponent->update(clock);
}

void Actor::setRootComponent(Component* root) {
    mpRootComponent = root;
}

}