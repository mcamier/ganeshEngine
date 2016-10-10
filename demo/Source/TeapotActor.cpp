#include "TeapotActor.hpp"

#include <ecs/ghModelComponent.hpp>
#include <ecs/ghBoxColliderComponent.hpp>

namespace ganeshEngine {

RTTI_IMPL(TeapotActor, Actor)

TeapotActor::TeapotActor(U32 id) :
        Actor(id) {
    _DEBUG("create teapot",LOG_CHANNEL::DEFAULT);
}

bool TeapotActor::vInitialize() {
    Actor::vInitialize();

    ModelComponent* cmodel = new ModelComponent();
    // cmodel->setMesh();
    // cmodel->setShader();
    // cmodel->setTexture();

    if (!addComponent(cmodel, 0)) return false;
    return addComponent(new BoxColliderComponent(), cmodel->getUID());
}

}
