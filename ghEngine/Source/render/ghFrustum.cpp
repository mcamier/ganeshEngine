#include "render/ghFrustum.hpp"
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

mat4 Frustum::getProjectionMatrix() {
	updateInternal();
	return mProjectionMatrix;
}

void Frustum::updateInternal() {
	if (mDirty) {
		mDirty = false;

		F32 tanFov = tan(mFieldOfView * 0.5f);
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
		mNears[PlaneCorner::TOP_RIGHT] = (forward * mNearClipDistance) + nearRight + nearUp;
		mNears[PlaneCorner::BOTTOM_RIGHT] = (forward * mNearClipDistance) + nearRight - nearUp;
		mNears[PlaneCorner::BOTTOM_LEFT] = (forward * mNearClipDistance) - nearRight - nearUp;

		mFars[PlaneCorner::TOP_LEFT] = (forward * mFarClipDistance) - farRight + farUp;
		mFars[PlaneCorner::TOP_RIGHT] = (forward * mFarClipDistance) + farRight + farUp;
		mFars[PlaneCorner::BOTTOM_RIGHT] = (forward * mFarClipDistance) + farRight - farUp;
		mFars[PlaneCorner::BOTTOM_LEFT] = (forward * mFarClipDistance) - farRight - farUp;

		mPlanes[FrustumPlane::TOP] = new Plane(mNears[PlaneCorner::TOP_LEFT], mFars[PlaneCorner::TOP_LEFT],
											   mFars[PlaneCorner::TOP_RIGHT]);
		mPlanes[FrustumPlane::BOTTOM] = new Plane(mNears[PlaneCorner::BOTTOM_RIGHT],
												  mFars[PlaneCorner::BOTTOM_RIGHT],
												  mFars[PlaneCorner::BOTTOM_LEFT]);
		mPlanes[FrustumPlane::NEAR] = new Plane(mNears[PlaneCorner::BOTTOM_RIGHT], mNears[PlaneCorner::TOP_RIGHT],
												mNears[PlaneCorner::TOP_LEFT]);
		mPlanes[FrustumPlane::FAR] = new Plane(mFars[PlaneCorner::BOTTOM_RIGHT], mFars[PlaneCorner::TOP_RIGHT],
											   mFars[PlaneCorner::TOP_LEFT]);
		mPlanes[FrustumPlane::LEFT] = new Plane(mNears[PlaneCorner::TOP_LEFT], mFars[PlaneCorner::TOP_LEFT],
												mFars[PlaneCorner::BOTTOM_LEFT]);
		mPlanes[FrustumPlane::RIGHT] = new Plane(mFars[PlaneCorner::BOTTOM_RIGHT],
												 mNears[PlaneCorner::BOTTOM_RIGHT], mNears[PlaneCorner::TOP_RIGHT]);

		F32 sx = (2 * mNearClipDistance) / (dNear * mAspectRatio + dNear * mAspectRatio);
		F32 sy = mNearClipDistance / dNear;
		F32 sz = -(mFarClipDistance + mNearClipDistance) / (mFarClipDistance - mNearClipDistance);
		F32 pz = -(2 * mFarClipDistance * mNearClipDistance) / (mFarClipDistance - mNearClipDistance);
		mProjectionMatrix = mat4();
		mProjectionMatrix[0][0] = sx;
		mProjectionMatrix[1][1] = sy;
		mProjectionMatrix[2][2] = sz;
		mProjectionMatrix[3][2] = pz;
		mProjectionMatrix[2][3] = -1;
	}
}

const F32 Frustum::getAspectRatio() {
	updateInternal();
	return mAspectRatio;
}

const U16 Frustum::getFieldOfView() {
	updateInternal();
	return mFieldOfView;
}

const F32 Frustum::getNearClipDistance() {
	updateInternal();
	return mNearClipDistance;
}

const F32 Frustum::getFarClipDistance() {
	updateInternal();
	return mFarClipDistance;
}

void Frustum::setAspectRatio(F32 newValue) {
	mAspectRatio = newValue;
	mDirty = true;
}

void Frustum::setFieldOfView(U16 newValue) {
	mFieldOfView = newValue;
	mDirty = true;
}

void Frustum::setNearClipDistance(F32 newValue) {
	mNearClipDistance = newValue;
	mDirty = true;
}

void Frustum::setFarClipDistance(F32 newValue) {
	mFarClipDistance = newValue;
	mDirty = true;
}

}