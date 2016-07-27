#include "ghSimulation.h"
#include "unistd.h"

namespace ganeshEngine {

    void Simulation::tick(U32 deltaNanosecond) {}

    Simulation &(*gSimulation)() = &Simulation::get;
}