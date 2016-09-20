#ifndef GANESHENGINE_GHICOMPONENT_H
#define GANESHENGINE_GHICOMPONENT_H

#include "ghHeaders.h"
#include "ghGameObject.h"
#include "ghClock.h"

#include <glm/glm.hpp>

using namespace glm;

namespace ganeshEngine {

//forward declaration
class Actor;

/**
 * Base class for all actor's component, it provides the update interface for all inherited component
 * Update call if toggleable
 */
class Component : public GameObject {
    friend class Actor;

RTTI_DECL()

protected:
    /** Switch update call activation */
    bool mUpdateEnabled;

public:
    explicit Component();
    explicit Component(bool updateEnabled);
    explicit Component(U32 id);
    explicit Component(U32 id, bool updateEnabled);

    /**
     * Call the component defined update method if the component currently allows update call
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
