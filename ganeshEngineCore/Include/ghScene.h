#ifndef GANESHENGINE_GHSCENE_H
#define GANESHENGINE_GHSCENE_H

#include "ghHeaders.h"
#include "ghSceneObject.h"
#include "ghCamera.h"
#include "ghSkybox.h"

namespace ganeshEngine {

    using namespace std;

/**
 * Scene graph data structure
 */
    class Scene {

    private:
        /**
         * Scene graph root node
         */
        SceneObject *mRoot;

        /**
         * Skybox used by the scene, might be nullptr
         */
        unique_ptr<Skybox> mSkybox;

        /**
         * Main camera used to draw the scene
         * the camera should belong to the scene graph
         */
        shared_ptr<Camera> mCamera;


    public:
        Scene() {
            mCamera = make_shared<Camera>(4.0f / 3.0f, 80, 1, 100);
        }

        Scene(SceneObject *root) : mRoot(root) {}

        ~Scene() {}

        /**
         * @param SceneObject*
         */
        void setRoot(SceneObject *newRoot);

        shared_ptr<Camera> getCamera();

        void setCamera(shared_ptr<Camera> camera);

        SceneObject *getRoot();

        /**
         * @param SceneObject*
         */
        void render();

        /**
         *
         */
        virtual void update(int deltaTime) {}
        virtual void vInitialize() = 0;
    };

}

#endif //GANESHENGINE_GHSCENE_H
