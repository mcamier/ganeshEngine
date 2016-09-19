#ifndef GANESHENGINE_GHBOXCOLLIDERCOMPONENT_H
#define GANESHENGINE_GHBOXCOLLIDERCOMPONENT_H


#include "ecs/ghActor.h"
#include "ecs/ghComponent.h"
#include "ghSerializable.h"
#include "ghIStream.h"
#include "ghRTTI.h"

#include "ghClock.h"

namespace ganeshEngine {

class BoxColliderComponent : public SceneComponent {

RTTI_DECL()

public:
    explicit BoxColliderComponent(U32 id) : SceneComponent(id, true) {}

    void vUpdate(const Clock& clock) override {}
};

}

#endif //GANESHENGINE_GHBOXCOLLIDERCOMPONENT_H
