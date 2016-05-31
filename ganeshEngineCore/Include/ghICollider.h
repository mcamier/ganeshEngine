#ifndef GANESHENGINE_GHCOLLIDER_H
#define GANESHENGINE_GHCOLLIDER_H

#include "ghHeaders.h"

namespace ganeshEngine {

using namespace glm;

class ICollider {

public:
	virtual bool vIsColliding(const vec3 &point) const { return false; }

	virtual bool vIsColliding(const vec3 &point, const F32 &radius) const { return false; }
};

}

#endif //GANESHENGINE_GHCOLLIDER_H
