#ifndef GANESHENGINE_GHMESHRENDERCOMPONENT_H
#define GANESHENGINE_GHMESHRENDERCOMPONENT_H

#include "ghActor.hpp"
#include "ghSceneComponent.hpp"
#include <util/ghSerializable.hpp>
#include <util/ghIStream.hpp>
#include <util/ghRTTI.hpp>
#include <util/ghILogger.hpp>
#include <util/ghClock.hpp>

#include "../resource/ghResourceHandler.hpp"
#include "../resource/ghResourceManager.hpp"

#include "../render/ghMesh.hpp"
#include "../render/ghShaderProgram.hpp"
#include "../render/ghTexture.hpp"

namespace ganeshEngine {

class ModelComponent : public SceneComponent {

RTTI_DECL()

private:
    ResourceHandler<Texture> mTexture;
    ResourceHandler<ShaderProgram> mShader;
    ResourceHandler<Mesh> mMesh;

public:
    explicit ModelComponent() : SceneComponent(gGetNextId()) {}
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
