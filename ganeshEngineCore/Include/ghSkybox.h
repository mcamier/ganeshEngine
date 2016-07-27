#ifndef GANESHENGINE_GHSKYBOX_H
#define GANESHENGINE_GHSKYBOX_H

#include "ghHeaders.h"
#include "ghSceneObject.h"

namespace ganeshEngine {

    using namespace std;

/**
 *
 */
    class Skybox : public SceneObject {
    private:

    public:
        Skybox() : SceneObject(SceneObjectType::SKYBOX) {};

        virtual ~Skybox() {}

        void preRender() override;

        void render() override;

        void postRender() override;
    };
}

#endif //GANESHENGINE_GHSKYBOX_H
