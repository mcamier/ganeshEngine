#ifndef GANESHENGINE_TEAPOTACTOR_H
#define GANESHENGINE_TEAPOTACTOR_H

#include <ecs/ghActor.hpp>
#include <util/ghRTTI.hpp>

namespace ganeshEngine {

class TeapotActor : public Actor {

    RTTI_DECL()

public:
    TeapotActor(U32 id);

protected:
    bool vInitialize() override;
};

}
#endif //GANESHENGINE_TEAPOTACTOR_H
