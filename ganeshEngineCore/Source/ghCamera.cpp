#include "ghCamera.h"

namespace ganeshEngine {

void Camera::lookAt(vec3 target, vec3 up) {
	mat4 translation, rotation;
	translation[3][0] = -getX();
	translation[3][1] = -getY();
	translation[3][2] = -getZ();
	vec3 mForward = target - getPosition();
	mForward = glm::normalize(mForward);

	mRight = mForward * up; // cross product here
	mUp = mRight * mForward; // cross product here

	rotation[0][0] = mRight.x;
	rotation[1][0] = mRight.y;
	rotation[2][0] = mRight.z;
	rotation[0][1] = mUp.x;
	rotation[1][1] = mUp.y;
	rotation[2][1] = mUp.z;
	rotation[0][2] = -mForward.x;
	rotation[1][2] = -mForward.y;
	rotation[2][2] = -mForward.z;

	mViewMatrix = translation * rotation;
}

const mat4 Camera::getProjection() {
	return mFrustum.getProjectionMatrix();
}

const mat4 Camera::getEyeMatrix() {
	return mViewMatrix;
}

void Camera::preRender() {
	SceneObject::preRender();
}

void Camera::render() {
	SceneObject::render();
}

void Camera::postRender() {
	SceneObject::postRender();
}

}