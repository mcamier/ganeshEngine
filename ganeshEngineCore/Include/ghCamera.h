#ifndef GANESHENGINE_GHCAMERA_H
#define GANESHENGINE_GHCAMERA_H

#include "ghHeaders.h"

namespace ganeshEngine {

using namespace std;


class SceneObject {
private:
	SceneObject* mpParent;
	vector<SceneObject*> mpChildren;

	SceneObject() {}
	~SceneObject() {}
	SceneObject(const SceneObject&) = delete;
	SceneObject& operator=(const SceneObject&) = delete;

	void appendChild(SceneObject*);

	void setParent(SceneObject*);
};


class Camera : public SceneObject {

};


class Actor: public SceneObject {

};


class Light: public SceneObject {

};

}

#endif //GANESHENGINE_GHCAMERA_H
