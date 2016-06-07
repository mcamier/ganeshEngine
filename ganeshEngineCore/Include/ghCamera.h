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

	SceneObject() {}
	~SceneObject() {}
	SceneObject(const SceneObject&) = delete;
	SceneObject& operator=(const SceneObject&) = delete;

	void appendChild(SceneObject*);

	void setParent(SceneObject*);
};


class Camera : public SceneObject {
private:
	Frustum* mpFrustum;
	IProjection* mpProjection;

public:
	Camera() {
		mpFrustum = new Frustum(4.0f/3.0f, 80, 1.0f, 1000.0f);
		mpProjection = new PerspectiveProjection();
	}
	~Camera() {}
};


class Actor: public SceneObject {

};


class Light: public SceneObject {

};

}

#endif //GANESHENGINE_GHCAMERA_H
