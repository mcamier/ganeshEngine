#ifndef GANESHENGINE_GHCOLLIDER_H
#define GANESHENGINE_GHCOLLIDER_H

#include "ghHeaders.h"

namespace ganeshEngine {

using namespace glm;


/**
 * Interface for objects providing collision testing feature
 */
class ICollider {

public:

	/**
	 * Test point collision against ICollider instance
	 *
	 * @param point 3D coordinates defining a point in space to test against the instance of ICollider
	 * @return True if point collides, False otherwise
	 */
	virtual bool vIsColliding(const vec3 &point) const { return false; }


	/**
	 * Test sphere collision against ICollider instance
	 *
	 * @param point 3D coordinates defining a the center of the sphere
	 * @param radius radius of the sphere
	 * @return True if point collides, False otherwise
	 */
	virtual bool vIsColliding(const vec3 &point, const F32 &radius) const { return false; }
};

}

#endif //GANESHENGINE_GHCOLLIDER_H
