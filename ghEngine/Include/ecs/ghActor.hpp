#ifndef GANESHENGINE_GHACTOR_H
#define GANESHENGINE_GHACTOR_H

#include <map>

#include <ecs/ghGameObject.hpp>
#include "ghComponent.hpp"
#include <ghTypes.hpp>
#include <util/ghClock.hpp>
#include <util/ghRTTI.hpp>
#include <util/ghIStream.hpp>

namespace ganeshEngine {

/**
 * Actor is an object that can be placed within a game world. It's a group of components. Components that belongs to an
 * actor defines it in some ways, behavior, rendering, etc.
 */
class Actor : public GameObject {
	friend class World;

RTTI_DECL()

private:
	/**
	 * Root component of the actor.
	 * If root component is an instance of SceneComponent the actor owner will be located within the game world,
	 * otherwise it will still belongs to the game world, but without any "physical" location
	 */
	Component *mpRootComponent;

	/**
	 * List of all components owned by the actor
	 */
	std::map<U32, Component*> mOwnedComponents;

	/**
	 * Defines if the actor must be ignored during a saving of the game world
	 */
	bool mbIgnoredOnSave;


public:
    explicit Actor();
    explicit Actor(bool ignoredOnSave);
    explicit Actor(U32 id);
    explicit Actor(U32 id, bool ignoredOnSave);

	/**
	 * Updating Actor results in updating all underlying owned components
	 * @param clock clock
	 */
    void update(const Clock &clock);

	/**
	 * Getter of mbIgnored on saving
	 * @param newValue true if actor must ignored on saving
	 */
	bool isIgnoredOnSave();

	/**
	 * Setter of mbIgnoredOnSave
	 * @param newValue
	 */
	void setIgnoredOnSave(bool newValue);

protected:
	/**
	 * Bind a component to the actor
	 * If componentParentId equals -1, the given component will be placed as root component of the object
	 * <p>
	 * If mRootComponent of the actor is nullptr, the given component will automatically be placed as root component
	 * <p>
	 * There is several cases where this method could return false :
	 *  - the actor doesn't contains a component with the given id
	 *  - you tried to bind a component to a non-SceneComponent
	 *  - the componentParentId is less or equals 0
	 *  - the componentParentId is equals the given component's id
	 *
	 * @param component
	 * @param componentParendId
	 * @return True if the component was placed in the actor, false otherwise
	 */
	bool addComponent(Component* component, U32 componentParendId);

	virtual bool vInitialize();

public:
	bool write(IStream& stream) const override;

	bool read(IStream& stream) override;
};

}

#endif //GANESHENGINE_GHACTOR_H
