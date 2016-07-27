#ifndef GANESHENGINE_GHSIMULATION_H
#define GANESHENGINE_GHSIMULATION_H

#include "ghHeaders.h"
#include "ghCore.h"
#include "ghSystem.h"

namespace ganeshEngine {

    class Simulation : public System<Simulation> {

    public:
        void tick(U32 deltaNanosecond);
    };

/**
 * Global getter of reference to the Simulation
 * @return reference to the Simulation
 */
    extern Simulation &(*gSimulation)();
}

#endif //GANESHENGINE_GHSIMULATION_H
