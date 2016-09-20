#include <ecs/ghSceneComponent.hpp>

using namespace std;

namespace ganeshEngine {

RTTI_ABSTRACT_IMPL(SceneComponent, Component)

SceneComponent::SceneComponent(U32 id) :
	Component(id),
	mModelTransform(Transform()),
	mParentRelativeModelTransform(Transform()),
	mSubComponents(vector<Component*>()) {}

SceneComponent::SceneComponent(U32 id, bool updateEnabled) :
	Component(id, updateEnabled),
	mModelTransform(Transform()),
	mParentRelativeModelTransform(Transform()),
	mSubComponents(vector<Component*>()){}


void SceneComponent::update(const Clock &clock) {
	Component::update(clock);

	for(Component* subComponent: mSubComponents)
		subComponent->update(clock);
}

void SceneComponent::registerSubComponent(Component * subComponent) {
	if(subComponent == nullptr) return;

	if( subComponent->mOwnerWorld != nullptr ||
		subComponent->mOwnerActor != nullptr) return;

	mSubComponents.push_back(subComponent);

	if(subComponent->getRTTI().isDerivedFrom(SceneComponent::rtti)) {
		((SceneComponent*)subComponent)->mParentComponent = this;
	}

	subComponent->mOwnerActor = mOwnerActor;

	/* if those two values are not null, it's means the parent component is already bound to a world so we have to bind
	 * the new one */
	if(mOwnerWorld && mOwnerActor) {
		mOwnerWorld->_registerComponent(this);
	}
}

}