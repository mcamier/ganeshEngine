#include "graphics/ghFrustum.h"
#include "math.h"
#include "math.h"

namespace ganeshEngine {

Frustum::Frustum(F32 aspectRatio, U16 fov, F32 nearClipDistance, F32 farClipDistance) {
	mAspectRatio = aspectRatio;
	mFieldOfView = fov;
	mNearClipDistance = nearClipDistance;
	mFarClipDistance = farClipDistance;
	updateInternal();
}

Frustum::~Frustum() {}

bool Frustum::vIsColliding(const vec3 &point) const {
	for(int i = 0 ; i<6; i++) {
		auto dotProduct = dot(mPlanes[i]->getNormal(), point);
		if(dotProduct <= 0.0f) {
			return false;
		}
	}
	return true;
}

bool Frustum::vIsColliding(const vec3 &point, const F32& radius) const {
	// TODO implement this
	return false;
}

void Frustum::updateInternal() {
	F32 tanFov = tan(mFieldOfView / 2.0f);
	F32 dNear = mNearClipDistance * tanFov;
	F32 dFar = mFarClipDistance * tanFov;

	vec3 right{1.0f, 0.0f, 0.0f};
	vec3 up{0.0f, 1.0f, 0.0f};
	vec3 forward{0.0f, 0.0f, 1.0f};
	vec3 nearRight = (mAspectRatio * right) * (dNear * tanFov);
	vec3 farRight = (mAspectRatio * right) * (dFar * tanFov);
	vec3 nearUp = up * (dNear * tanFov);
	vec3 farUp = up * (dFar * tanFov);

	mNears[PlaneCorner::TOP_LEFT] = (forward * mNearClipDistance) - nearRight + nearUp;
	mNears[PlaneCorner::TOP_RIGHT] = (forward * mNearClipDistance ) + nearRight + nearUp;
	mNears[PlaneCorner::BOTTOM_RIGHT] = (forward * mNearClipDistance) + nearRight - nearUp;
	mNears[PlaneCorner::BOTTOM_LEFT] = (forward * mNearClipDistance) - nearRight - nearUp;

	mFars[PlaneCorner::TOP_LEFT] = (forward * mFarClipDistance) - farRight + farUp;
	mFars[PlaneCorner::TOP_RIGHT] = (forward * mFarClipDistance) + farRight + farUp;
	mFars[PlaneCorner::BOTTOM_RIGHT] = (forward * mFarClipDistance) + farRight - farUp;
	mFars[PlaneCorner::BOTTOM_LEFT] = (forward * mFarClipDistance) - farRight - farUp;

	mPlanes[FrustumPlane::TOP] = new Plane(mNears[PlaneCorner::TOP_LEFT], mFars[PlaneCorner::TOP_LEFT], mFars[PlaneCorner::TOP_RIGHT]); //ok
	mPlanes[FrustumPlane::BOTTOM] = new Plane(mNears[PlaneCorner::BOTTOM_RIGHT], mFars[PlaneCorner::BOTTOM_RIGHT], mFars[PlaneCorner::BOTTOM_LEFT]); //ok
	mPlanes[FrustumPlane::NEAR] = new Plane(mNears[PlaneCorner::BOTTOM_RIGHT], mNears[PlaneCorner::TOP_RIGHT], mNears[PlaneCorner::TOP_LEFT]); //ok
	mPlanes[FrustumPlane::FAR] = new Plane(mFars[PlaneCorner::BOTTOM_RIGHT], mFars[PlaneCorner::TOP_RIGHT], mFars[PlaneCorner::TOP_LEFT]); //ok
	mPlanes[FrustumPlane::LEFT] = new Plane(mNears[PlaneCorner::TOP_LEFT], mFars[PlaneCorner::TOP_LEFT], mFars[PlaneCorner::BOTTOM_LEFT]); //ok
	mPlanes[FrustumPlane::RIGHT] = new Plane(mFars[PlaneCorner::BOTTOM_RIGHT], mNears[PlaneCorner::BOTTOM_RIGHT], mNears[PlaneCorner::TOP_RIGHT]); //ok
}

const F32 Frustum::getAspectRatio() const {
	return mAspectRatio;
}

const U16 Frustum::getFieldOfView() const {
	return mFieldOfView;
}


const F32 Frustum::getNearClipDistance() const {
	return mNearClipDistance;
}

const F32 Frustum::getFarClipDistance() const {
	return mFarClipDistance;
}

void Frustum::getAspectRatio(F32 newValue) {
	mAspectRatio = newValue;
	updateInternal();
}

void Frustum::getFieldOfView(U16 newValue) {
	mFieldOfView = newValue;
	updateInternal();
}

void Frustum::getNearClipDistance(F32 newValue) {
	mNearClipDistance = newValue;
	updateInternal();
}

void Frustum::getFarClipDistance(F32 newValue) {
	mFarClipDistance = newValue;
	updateInternal();
}

}