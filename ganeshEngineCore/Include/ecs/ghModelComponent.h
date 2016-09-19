#ifndef GANESHENGINE_GHMESHRENDERCOMPONENT_H
#define GANESHENGINE_GHMESHRENDERCOMPONENT_H


#include "ecs/ghActor.h"
#include "ecs/ghComponent.h"
#include "ghSerializable.h"
#include "ghIStream.h"
#include "ghRTTI.h"

#include "ghResourceHandler.h"
#include "ghResourceManager.h"
#include "ghClock.h"

#include "graphics/ghMesh.h"
#include "graphics/ghShaderProgram.h"
#include "graphics/ghTexture.h"

namespace ganeshEngine {

class ModelComponent : public SceneComponent {

RTTI_DECL()

private:
    ResourceHandler<Texture> mTexture;
    ResourceHandler<ShaderProgram> mShader;
    ResourceHandler<Mesh> mMesh;

public:
    explicit ModelComponent(U32 id) : SceneComponent(id) {}


    void setTexture(ResourceHandler<Texture> texture) {
        mTexture = texture;
    }

    void setMesh(ResourceHandler<Mesh> mesh) {
        mMesh = mesh;
    }

    void setShader(ResourceHandler<ShaderProgram> shader) {
        mShader = shader;
    }

    void vUpdate(const Clock& clock) override {
        _DEBUG("Update ModelComponent", LOG_CHANNEL::DEFAULT);
    }

};

}

#endif //GANESHENGINE_GHMESHRENDERCOMPONENT_H
