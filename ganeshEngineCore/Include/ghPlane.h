#ifndef GANESHENGINE_GHPLANE_H
#define GANESHENGINE_GHPLANE_H

#include "ghHeaders.h"
#include <glm/glm.hpp>
#include "ghICollider.h"

namespace ganeshEngine {

using namespace std;
using namespace glm;

enum PlaneCorner {
	TOP_LEFT = 0,
	TOP_RIGHT = 1,
	BOTTOM_RIGHT = 2,
	BOTTOM_LEFT = 3,
};

class Plane : public ICollider {

private:
	vec3 mCorners[4];
	vec3 mNormal;

	Plane(const vec3 topLeft, const vec3 topRight, const vec3 bottomRight, const vec3 bottomLeft);

public:
	~Plane();

	static Plane* make(const vec3 pt1, const vec3 pt2, const vec3 pt3, const vec3 pt4);

	static Plane* make(const vec3 pt1, const vec3 pt2, const vec3 pt3);

	bool vIsColliding(const vec3 &point) const override;

	bool vIsColliding(const vec3 &point, const F32 &radius) const override;

	const vec3 getNormal() const;
};

}

#endif //GANESHENGINE_GHPLANE_H
