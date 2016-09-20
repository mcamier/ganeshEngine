#include "ghScene.hpp"

#include "util/ghBasicStream.hpp"

namespace ganeshEngine {

Scene::Scene() : mActors(vector<Actor *>()) {}

Scene::~Scene() {}

void Scene::addActor(Actor *newActor) {
	mActors.push_back(newActor);
}

void Scene::vUpdate(const Clock &clock) {
	for (Actor *actor : mActors) {
		actor->update(clock);
	}
}

void Scene::save(string filename) {
	BasicStream save(filename);
	if (save.open()) {
		// write some informations about the scene

		for (Actor *actor : mActors) {
			if (!actor->isIgnoredOnSave()) {
				actor->write(save);
			}
		}
		save.close();
	}
}

void Scene::load(string filename) {
	BasicStream load(filename);
	if (load.open()) {
		// read some informations about the scene
		// read actors and store them
		load.close();
	}
}

}