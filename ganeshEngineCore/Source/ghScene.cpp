#include "ghScene.h"

namespace ganeshEngine {

Scene::Scene() : mActors(vector<Actor*>()) {}

Scene::~Scene() {}

void Scene::addActor(Actor* newActor) {
    mActors.push_back(newActor);
}

void render();

void Scene::vUpdate(const Clock &clock) {
    for(Actor* actor : mActors) {
        actor->update(clock);
    }
}

}