#include "ghScene.h"

namespace ganeshEngine {

void Scene::setRoot(SceneObject *newRoot) {
	mRoot = newRoot;
}

SceneObject* Scene::getRoot() {
	return mRoot;
}


void Scene::draw() {
	mRoot->draw();
}

}