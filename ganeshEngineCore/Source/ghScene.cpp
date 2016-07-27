#include "ghScene.h"

namespace ganeshEngine {

    void Scene::setRoot(SceneObject *newRoot) {
        mRoot = newRoot;
        mRoot->mOwner = this;
    }

    SceneObject *Scene::getRoot() {
        return mRoot;
    }

    shared_ptr<Camera> Scene::getCamera() {
        return mCamera;
    }

    void Scene::setCamera(shared_ptr<Camera> camera) {
        mCamera = camera;
    }

    void Scene::render() {
        mRoot->render();
    }

}