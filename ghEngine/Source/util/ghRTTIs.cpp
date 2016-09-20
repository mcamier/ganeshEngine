#include "ecs/ghComponent.hpp"
#include "ecs/ghSceneComponent.hpp"
#include "ecs/ghModelComponent.hpp"
#include "ecs/ghBoxColliderComponent.hpp"
#include "ecs/ghCameraComponent.hpp"
#include "ecs/ghGameObject.hpp"


namespace ganeshEngine {

RTTI_IMPL(ModelComponent, SceneComponent)
RTTI_IMPL(BoxColliderComponent, SceneComponent)
RTTI_IMPL(CameraComponent, SceneComponent)

}