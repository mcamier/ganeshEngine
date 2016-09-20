#include "ghComponent.h"
#include "ghSceneComponent.h"
#include "ghModelComponent.h"
#include "ghBoxColliderComponent.h"
#include "ghCameraComponent.h"
#include "ghFactory.h"

#include "ghRTTI.h"

namespace ganeshEngine {

RTTI_DEF_BASE(GameObject)

RTTI_DEF(Component, GameObject)
RTTI_DEF(SceneComponent, Component)
RTTI_DEF(ModelComponent, SceneComponent)
RTTI_DEF(BoxColliderComponent, SceneComponent)
RTTI_DEF(CameraComponent, SceneComponent)

}