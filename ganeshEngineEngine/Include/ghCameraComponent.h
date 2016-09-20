#ifndef GANESHENGINE_GHCAMERACOMPONENT_H
#define GANESHENGINE_GHCAMERACOMPONENT_H

#include "ghRTTI.h"
#include "ghClock.h"
#include "ghSceneComponent.h"

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
