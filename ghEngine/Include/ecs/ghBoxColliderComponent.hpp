#ifndef GANESHENGINE_GHBOXCOLLIDERCOMPONENT_H
#define GANESHENGINE_GHBOXCOLLIDERCOMPONENT_H

#include "ghActor.hpp"
#include "ghSceneComponent.hpp"
#include <util/ghSerializable.hpp>
#include <util/ghIStream.hpp>
#include <util/ghRTTI.hpp>

#include <util/ghClock.hpp>

namespace ganeshEngine {

class BoxColliderComponent : public SceneComponent {

RTTI_DECL()

public:
    explicit BoxColliderComponent(U32 id) : SceneComponent(id, true) {}

    void vUpdate(const Clock& clock) override {}
};

}

#endif //GANESHENGINE_GHBOXCOLLIDERCOMPONENT_H
