#include "ghPlane.h"

namespace ganeshEngine {

Plane::Plane(const vec3 pt1, const vec3 pt2, const vec3 pt3, const vec3 pt4) {
	mCorners[0] = pt1;
	mCorners[1] = pt2;
	mCorners[2] = pt3;
	mCorners[3] = pt4;
	vec3 pt1pt2{pt2.x - pt1.x, pt2.y - pt1.y, pt2.z - pt1.z};
	vec3 pt1pt3{pt3.x - pt1.x, pt3.y - pt1.y, pt3.z - pt1.z};
	mNormal = normalize(cross(pt1pt2, pt1pt3));
}

Plane::~Plane() { }

Plane* Plane::make(const vec3 pt1, const vec3 pt2, const vec3 pt3, const vec3 pt4) {
	vec3 pt1pt2{pt2.x - pt1.x, pt2.y - pt1.y, pt2.z - pt1.z};
	vec3 pt1pt3{pt3.x - pt1.x, pt3.y - pt1.y, pt3.z - pt1.z};
	vec3 pt1pt4{pt4.x - pt1.x, pt4.y - pt1.y, pt4.z - pt1.z};

	auto dotResult = dot(pt1pt2, cross(pt1pt3, pt1pt4));
	if(dotResult != 0.0f) {
		throw std::exception();
	}

	return new Plane(pt1, pt2, pt3, pt4);
}

Plane* Plane::make(const vec3 pt1, const vec3 pt2, const vec3 pt3) {
	return new Plane(pt1, pt2, pt3, pt3);
}

bool Plane::vIsColliding(const vec3 &point) const {
	// TODO implement this
	return false;
}

bool Plane::vIsColliding(const vec3 &point, const F32 &radius) const {
	// TODO implement this
	return false;
}

const vec3 Plane::getNormal() const {
	return mNormal;
}

}