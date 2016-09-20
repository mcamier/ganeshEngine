#ifndef GANESHENGINE_GHICOMPONENT_H
#define GANESHENGINE_GHICOMPONENT_H

#include "ghGameObject.hpp"
#include "../util/ghClock.hpp"
#include "../ghWorld.hpp"
#include "../ghTypes.hpp"
#include "../util/ghRTTI.hpp"


namespace ganeshEngine {

//forward declaration
class Actor;
class SceneComponent;

/**
 * Base class for all actor's component, it provides the update interface for all inherited component
 * Update call if toggleable
 */
class Component : public GameObject {
    friend class Actor;
    friend class World;
    friend class SceneComponent;

RTTI_DECL()

private:
    /**
     * Pointer of the world where this component is registered
     * Is nullptr if the component is not bound to any game world, otherwise we can expect the component to be well bound
     */
    World* mOwnerWorld;

    /**
     * pointer of the actor owning the component
     * Is nullptr if the component doesn't belongs to any actor, otherwise we can expect the actor to be well bound
     * If mOwnerActor is nullptr while mOwnerWorld is not, will lead to invalid behavior because a component can live
     * in a World while not being to any Actor
     */
    Actor* mOwnerActor;

protected:
    /**
     * Any component can be attached to a SceneComponent, in that case this pointer leads to the parent component,
     * otherwise it stay null
     */
    SceneComponent *mParentComponent;

protected:
    /**
     * Switch update call activation
     * */
    bool mUpdateEnabled;

public:
    explicit Component();
    explicit Component(bool updateEnabled);
    explicit Component(U32 id);
    explicit Component(U32 id, bool updateEnabled);

    /**
     * Call the component defined update method if the component currently allows update call.
     * @note In order to update itself the component also check whether it is well bound (not null values for mOwnerActor and
     * mOwnerWorld)
     *
     * @param clock clock
     */
    virtual void update(const Clock &clock);

    /**
     * Turn on update for this component
     */
    void activeUpdate();

    /**
     * Turn off update for this component
     */
    void deactiveUpdate();

protected:
    /**
     * Component custom update behavior
     *
     * @param clock clock
     */
    virtual void vUpdate(const Clock &clock) = 0;
};

}

#endif //GANESHENGINE_GHICOMPONENT_H
