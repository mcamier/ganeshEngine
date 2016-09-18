#ifndef GANESHENGINE_GHACTOR_H
#define GANESHENGINE_GHACTOR_H

#include "ghHeaders.h"
#include "ecs/ghIComponent.h"

namespace ganeshEngine {

/**
 *
 */
class Actor : public GameObject {

RTTI_DECL()

private:
    Component *mpRootComponent;

public:
    explicit Actor(U32 id);

    void update(const Clock &clock);

    void setRootComponent(Component *root);
};

}

#endif //GANESHENGINE_GHACTOR_H
