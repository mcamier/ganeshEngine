#ifndef GANESHENGINE_GHCAMERACOMPONENT_H
#define GANESHENGINE_GHCAMERACOMPONENT_H

#include "ghSceneComponent.hpp"
#include "../ghTypes.hpp"
#include "../util/ghRTTI.hpp"
#include "../util/ghClock.hpp"

namespace ganeshEngine {

class CameraComponent : public SceneComponent {

RTTI_DECL()

public:
    explicit CameraComponent() : SceneComponent(gGetNextId()) {}
    explicit CameraComponent(U32 id) : SceneComponent(id) {}

    void vUpdate(const Clock& clock) override {}
};

}

#endif //GANESHENGINE_GHCAMERACOMPONENT_H
