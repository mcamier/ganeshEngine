#ifndef GANESHENGINE_GHCAMERA_H
#define GANESHENGINE_GHCAMERA_H

#include "ghHeaders.h"
#include "graphics/ghFrustum.h"
#include "ghProjection.h"

namespace ganeshEngine {

using namespace std;


class SceneObject {
private:
	SceneObject* mpParent;
	vector<SceneObject*> mpChildren;
	
	SceneObject() : mpParent(nullptr) {}
	~SceneObject() {}
	SceneObject(const SceneObject&) = delete;
	SceneObject& operator=(const SceneObject&) = delete;

	void setParent(SceneObject* object);

public:
	void appendChild(SceneObject* object);
};

}

#endif //GANESHENGINE_GHCAMERA_H
