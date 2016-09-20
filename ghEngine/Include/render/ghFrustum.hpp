#ifndef GANESHENGINE_GHFRUSTUM_H
#define GANESHENGINE_GHFRUSTUM_H

#include "ghTypes.hpp"
#include "ghPlane.hpp"

#include <glm/glm.hpp>

namespace ganeshEngine {

using namespace std;
using namespace glm;


enum FrustumPlane {
    NEAR = 0x1,
    FAR = 0x2,
    BOTTOM = 0x3,
    TOP = 0x4,
    LEFT = 0x5,
    RIGHT = 0x6
};

/**
 *
 */
class Frustum {
private:
    U16 mFieldOfView;
    F32 mAspectRatio;
    F32 mNearClipDistance;
    F32 mFarClipDistance;
    vec3 mNears[4];
    vec3 mFars[4];
    Plane *mPlanes[6];
    mat4 mProjectionMatrix;
    bool mDirty{true};

public:

    Frustum(F32 aspectRatio, U16 fov, F32 nearClipDistance, F32 farClipDistance);

    ~Frustum();

    void updateInternal();

    const F32 getAspectRatio();

    const U16 getFieldOfView();

    const F32 getNearClipDistance();

    const F32 getFarClipDistance();

    mat4 getProjectionMatrix();

    void setAspectRatio(F32 newValue);

    void setFieldOfView(U16 newValue);

    void setNearClipDistance(F32 newValue);

    void setFarClipDistance(F32 newValue);
};

}


#endif //GANESHENGINE_GHFRUSTUM_H
