#ifndef GANESHENGINE_GHSCENECOMPONENT_H
#define GANESHENGINE_GHSCENECOMPONENT_H

#include "ghComponent.hpp"
#include "ghActor.hpp"
#include <ecs/ghGameObject.hpp>
#include <util/ghClock.hpp>
#include "../ghTransform.hpp"

#include <vector>

namespace ganeshEngine {

/**
 * Base component for all component that could be located within the scene its owner belongs
 * SceneComponent could aldo embed tree of sub components, which may, or not, depends of parent's component location if
 * parent's component is SceneComponent as well
 */
class SceneComponent : public Component {
	friend class Actor;

RTTI_DECL()

	/**
	 * Transformation of the object
	 */
	Transform mModelTransform;

	/**
	 * Transformation of the object in the world, relative to its parents
	 */
	Transform mParentRelativeModelTransform;

protected:
	std::vector<Component *> mSubComponents;

public:
	explicit SceneComponent(U32 id);
	explicit SceneComponent(U32 id, bool updateEnabled);

public:
	/**
	 * Call the component custom vUpdate overloaded method, then call all sub component udpate method
	 * @param clock
	 */
	void update(const Clock &clock) override;

	void registerSubComponent(Component* subComponent);

	/**
	 * Compute the world relative location, rotation and scale accordingly the component informations and parent
	 * component's information recursively
	 */
	void refresh();

	/**
	 * Set the component's flag as dirty, then do the same for all sub components which are also instances of
	 * SceneComponent
	 */
	void setDirty();

};

}

#endif //GANESHENGINE_GHSCENECOMPONENT_H
