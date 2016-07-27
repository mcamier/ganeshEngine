#ifndef GANESHENGINE_GHCAMERA_H
#define GANESHENGINE_GHCAMERA_H

#include "ghHeaders.h"
#include "graphics/ghFrustum.h"
#include "ghSceneObject.h"

namespace ganeshEngine {

    using namespace std;

/**
 *
 */
    class Camera : public SceneObject {
    private:
        Frustum mFrustum;

        vec3 mForward;
        vec3 mUp;
        vec3 mRight;
        mat4 mViewMatrix;

    public:
        Camera(F32 aspectRatio, U16 fov, F32 near, F32 far) :
                SceneObject(SceneObjectType::CAMERA),
                mFrustum(Frustum(aspectRatio, fov, near, far)) {};

        virtual ~Camera() {}

        /**
         * Based on the position of the sceneObject bound
         *
         * @param target Where the camera must look at in the 3d space
         * @param up Up vector of the camera
         */
        void lookAt(vec3 target, vec3 up);

        /**
         * Returns the matrix used to transform coordinates into homogeneous coords
         *
         * @return mat4 the projection matrix
         */
        const mat4 getProjection();

        /**
         * Returns the matrix used to transform positions into position relative to the camera
         * position and rotation
         *
         * @return mat4 the transform matrix
         */
        const mat4 getEyeMatrix();

        void preRender() override;

        void render() override;

        void postRender() override;
    };


}

#endif //GANESHENGINE_GHCAMERA_H
