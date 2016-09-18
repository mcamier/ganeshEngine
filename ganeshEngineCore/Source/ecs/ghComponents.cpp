#include "ecs/ghModelComponent.h"
#include "ecs/ghBoxColliderComponent.h"
#include "ghFactory.h"

#include "ghRTTI.h"

namespace ganeshEngine {

RTTI_DEF_BASE(GameObject)

RTTI_DEF(Component, GameObject)
RTTI_DEF(SceneComponent, Component)
RTTI_DEF(ModelComponent, SceneComponent)
RTTI_DEF(BoxColliderComponent, SceneComponent)

CREATOR_IMPL(ModelComponent)
CREATOR_IMPL(BoxColliderComponent)
}