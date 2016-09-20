#include "ghTransform.hpp"

namespace ganeshEngine {

Transform::Transform() : mmMatrix(mat4()),
						 mLocation(vec3()),
						 mRotation(vec3()),
						 mScale(vec3()),
						 mbDirty(true) {}

Transform::~Transform() {}


vec3 Transform::getPos() const {
	return mLocation;
}
vec3 Transform::getRotation() const {
	return mRotation;
}

vec3 Transform::getScale() const {
	return mScale;
}

void Transform::setPos(const vec3 newPosition) {
	mLocation = newPosition;
}
void Transform::setRotation(const vec3 newRotation) {
	mLocation = newRotation;
}

void Transform::setScale(const vec3 newScale) {
	mLocation = newScale;
}


float Transform::getPosX()  const{
	return mLocation.x;
}

void Transform::setPosX(float value) {
	mbDirty = true;
	mLocation.x = value;
}

void Transform::addToPosX(float value) {
	mbDirty = true;
	mLocation.x += value;
}

float Transform::getPosY() const {
	return mLocation.y;
}

void Transform::setPosY(float value) {
	mbDirty = true;
	mLocation.y = value;
}

void Transform::addToPosY(float value) {
	mbDirty = true;
	mLocation.y += value;
}

float Transform::getPosZ() const {
	return mLocation.z;
}

void Transform::setPosZ(float value) {
	mbDirty = true;
	mLocation.z = value;
}

void Transform::addToPosZ(float value) {
	mbDirty = true;
	mLocation.z += value;
}

float Transform::getRotX() const {
	return mRotation.x;
}

void Transform::setRotX(float value) {
	mbDirty = true;
	mRotation.x = value;
}

void Transform::addToRotX(float value) {
	mbDirty = true;
	mRotation.x += value;
}

float Transform::getRotY() const {
	return mRotation.y;
}

void Transform::setRotY(float value) {
	mbDirty = true;
	mRotation.y = value;
}

void Transform::addToRotY(float value) {
	mbDirty = true;
	mRotation.y += value;
}

float Transform::getRotZ() const {
	return mRotation.z;
}

void Transform::setRotZ(float value) {
	mbDirty = true;
	mRotation.z = value;
}

void Transform::addToRotZ(float value) {
	mbDirty = true;
	mRotation.z += value;
}

float Transform::getScaleX() const {
	return mScale.x;
}

void Transform::setScaleX(float value) {
	mbDirty = true;
	mScale.x = value;
}

void Transform::addToScaleX(float value) {
	mbDirty = true;
	mScale.x += value;
}

float Transform::getScaleY() const {
	return mScale.y;
}

void Transform::setScaleY(float value) {
	mbDirty = true;
	mScale.y = value;
}

void Transform::addToScaleY(float value) {
	mbDirty = true;
	mScale.y += value;
}

float Transform::getScaleZ() const {
	return mScale.z;
}

void Transform::setScaleZ(float value) {
	mbDirty = true;
	mScale.z = value;
}

void Transform::addToScaleZ(float value) {
	mbDirty = true;
	mScale.z += value;
}

void Transform::refresh() {
	if(mbDirty) {
		mbDirty = false;
		// recompute matrix
	}
}

}