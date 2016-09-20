#include "render/ghPlane.hpp"

namespace ganeshEngine {

    Plane::Plane(const vec3 pt1, const vec3 pt2, const vec3 pt3) {
        mCorners[0] = pt1;
        mCorners[1] = pt2;
        mCorners[2] = pt3;
        vec3 pt1pt2{pt2.x - pt1.x, pt2.y - pt1.y, pt2.z - pt1.z};
        vec3 pt2pt3{pt3.x - pt2.x, pt3.y - pt2.y, pt3.z - pt2.z};
        mNormal = normalize(cross(pt1pt2, pt2pt3));
    }

    Plane::~Plane() {}

    bool Plane::isToward(const vec3 &point) const {
        float dotResult = dot(mNormal, point);
        return (dotResult >= 0.0f);
    }

    bool Plane::isToward(const vec3 &point, const F32 &radius) const {
        // TODO implement this
        return false;
    }

    const vec3 Plane::getNormal() const {
        return mNormal;
    }

}