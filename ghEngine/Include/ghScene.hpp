#ifndef GANESHENGINE_GHSCENE_H
#define GANESHENGINE_GHSCENE_H

#include "ghHeaders.hpp"
#include "util/ghClock.hpp"
#include "ecs/ghActor.hpp"

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

	void save(string filename);
	void load(string filename);

};

}

#endif //GANESHENGINE_GHSCENE_H
