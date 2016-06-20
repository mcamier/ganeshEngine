#ifndef GANESHENGINE_GHSCENE_H
#define GANESHENGINE_GHSCENE_H

#include "ghHeaders.h"
#include "ghSceneObject.h"

namespace ganeshEngine {

using namespace std;


/**
 * Scene graph data structure
 */
class Scene {

private:
	SceneObject *mRoot;

public:
	Scene() {}
	Scene(SceneObject *root) : mRoot(root) {}
	~Scene() {}

	void setRoot(SceneObject *newRoot);

	SceneObject* getRoot();

	void draw();
};

}

#endif //GANESHENGINE_GHSCENE_H
