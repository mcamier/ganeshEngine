#ifndef GANESHENGINE_GHPLANE_H
#define GANESHENGINE_GHPLANE_H

#include "ghTypes.hpp"
#include <glm/glm.hpp>

namespace ganeshEngine {

using namespace std;
using namespace glm;

enum PlaneCorner {
    TOP_LEFT = 0,
    TOP_RIGHT = 1,
    BOTTOM_RIGHT = 2,
    BOTTOM_LEFT = 3,
};

class Plane {

private:
    vec3 mCorners[3];
    vec3 mNormal;

public:
    Plane(const vec3 pt1, const vec3 pt2, const vec3 pt3);

    ~Plane();

    bool isToward(const vec3 &point) const;

    bool isToward(const vec3 &point, const F32 &radius) const;

    const vec3 getNormal() const;
};

}

#endif //GANESHENGINE_GHPLANE_H
