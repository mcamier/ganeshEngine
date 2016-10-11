#ifndef GANESHENGINE_GHMESHRENDERCOMPONENT_H
#define GANESHENGINE_GHMESHRENDERCOMPONENT_H

#include "ghActor.hpp"
#include "ghSceneComponent.hpp"
#include <util/ghSerializable.hpp>
#include <util/ghIStream.hpp>
#include <util/ghRTTI.hpp>
#include <util/ghILogger.hpp>
#include <util/ghClock.hpp>
#include <util/ghStringId.hpp>

#include "../resource/ghResourceHandler.hpp"
#include "../resource/ghResourceManager.hpp"

#include "../render/ghMesh.hpp"
#include "../render/ghShaderProgram.hpp"
#include "../render/ghTexture.hpp"

namespace ganeshEngine {

class ModelComponent : public SceneComponent {

RTTI_DECL()

private:
    stringId mMeshStringId;

public:
    explicit ModelComponent() : SceneComponent(gGetNextId()) {}
    explicit ModelComponent(U32 id) : SceneComponent(id) {}

    void setMeshStringId(stringId mesh) {
        mMeshStringId = mesh;
    }

    stringId getMeshStringId() {
        return mMeshStringId;
    }

    void vUpdate(const Clock& clock) override {
        _DEBUG("Update ModelComponent", LOG_CHANNEL::DEFAULT);
    }

};

}

#endif //GANESHENGINE_GHMESHRENDERCOMPONENT_H
