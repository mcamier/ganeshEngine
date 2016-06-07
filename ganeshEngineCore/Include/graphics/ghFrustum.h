#ifndef GANESHENGINE_GHFRUSTUM_H
#define GANESHENGINE_GHFRUSTUM_H

#include "../ghHeaders.h"
#include "../ghPlane.h"
#include "../ghICollider.h"

#include <glm/glm.hpp>

namespace ganeshEngine {

using namespace std;
using namespace glm;


enum FrustumPlane {
	NEAR = 0,
	FAR = 1,
	BOTTOM = 2,
	TOP = 3,
	LEFT = 4,
	RIGHT = 5
};

class Frustum : public ICollider{
private:
	F32 mAspectRatio;
	U16 mFieldOfView;
	F32 mNearClipDistance;
	F32 mFarClipDistance;

	vec3 mNears[4];
	vec3 mFars[4];

	Plane* mPlanes[6];

public:

	Frustum(F32 aspectRatio, U16 fov, F32 nearClipDistance, F32 farClipDistance);

	~Frustum();

	bool vIsColliding(const vec3 &point) const override;

	bool vIsColliding(const vec3 &point, const F32& radius) const override;

	void updateInternal();

	const F32 getAspectRatio() const;

	const U16 getFieldOfView() const;

	const F32 getNearClipDistance() const;

	const F32 getFarClipDistance() const;

	void getAspectRatio(F32 newValue);

	void getFieldOfView(U16 newValue);

	void getNearClipDistance(F32 newValue);

	void getFarClipDistance(F32 newValue);
};

}


#endif //GANESHENGINE_GHFRUSTUM_H
