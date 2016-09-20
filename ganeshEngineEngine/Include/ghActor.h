#ifndef GANESHENGINE_GHACTOR_H
#define GANESHENGINE_GHACTOR_H

#include "ghHeaders.h"
#include "ghComponent.h"

namespace ganeshEngine {

/**
 * Actor is an object that can be placed within a game world. It's a group of components. Components that belongs to an
 * actor defines it in some ways, behavior, rendering, etc.
 */
class Actor : public GameObject {

RTTI_DECL()

private:
	/**
	 * Root component of the actor.
	 * If root component is an instance of SceneComponent the actor owner will be located within the game world,
	 * otherwise it will still belongs to the game world, but without any "physical" location
	 */
    Component *mpRootComponent;

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
	 * Set the root component bound to the actor
	 * If root component is an instance of SceneComponent the actor owner will be located within the game world,
	 * otherwise it will still belongs to the game world, but without any "physical" location
	 *
	 * @param root component to set as root of the actor
	 */
    void setRootComponent(Component *root);

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
