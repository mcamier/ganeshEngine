#ifndef GANESHENGINE_GHSCENE_H
#define GANESHENGINE_GHSCENE_H

#include "ghHeaders.h"
#include "ghClock.h"
#include "ecs/ghActor.h"

namespace ganeshEngine {

using namespace std;


class Scene {

protected:
    vector<Actor*> mActors;

public:
    Scene();

    ~Scene();

    void addActor(Actor* newActor);

    void render();

    virtual void vUpdate(const Clock &clock);

    virtual void vInitialize() = 0;
};

}

#endif //GANESHENGINE_GHSCENE_H
