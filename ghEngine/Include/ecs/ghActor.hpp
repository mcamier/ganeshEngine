#ifndef GANESHENGINE_GHACTOR_H
#define GANESHENGINE_GHACTOR_H

#include <vector>

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
     * Pointer of the world where this actor is registered
     * Is nullptr if the actor is not bound to any game world, otherwise we can expect the actor to be well bound
     */
	World* mOwnerWorld;

	/**
	 * Root component of the actor.
	 * If root component is an instance of SceneComponent the actor owner will be located within the game world,
	 * otherwise it will still belongs to the game world, but without any "physical" location
	 */
	Component *mpRootComponent;

	/**
	 * List of all components owned by the actor
	 */
	std::vector<Component*> mOwnedComponents;

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
	 *
	 * @param component
	 */
	void registerComponent(Component* component);

	/**
	 *
	 * @param parentComponentId
	 * @param component
	 */
	void registerSubComponent(U32 parentComponentId, Component* component);

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

	bool write(IStream& stream) const override;

	bool read(IStream& stream) override;
};

}

#endif //GANESHENGINE_GHACTOR_H
