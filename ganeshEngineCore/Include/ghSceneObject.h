#ifndef GANESHENGINE_GHSCENEOBJECT_H
#define GANESHENGINE_GHSCENEOBJECT_H

#include "ghHeaders.h"
#include "graphics/ghGLModel.h"

namespace ganeshEngine {

enum class SceneObjectType : U32 {
    DYNAMIC,
    STATIC,
    LIGHT,
    SKYBOX
};



class IComponent {};



class CameraComponent : public IComponent {
private:
    //P*rojection projection

    SceneObject *mParent;
    vec3 mForward;
    vec3 mUp;
    vec3 mRight;
    mat4 mViewMatrix;

public:
    CameraComponent() {};
    ~CameraComponent() {}

    /**
     * Based on the position of the sceneObject bound
     *
     * @param target Where the camera must look at in the 3d space
     * @param up Up vector of the camera
     */
    void lookAt(vec3 target, vec3 up) {
        mat4 translation, rotation;
        translation[3][0] = -mParent->getX();
        translation[3][1] = -mParent->getY();
        translation[3][2] = -mParent->getZ();
        vec3 mForward = target - mParent->getPosition();
        mForward.normalize();

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

        mViewMatrix = rotation * translation;
    }

    /**
     * TODO
     */
    const mat4 getProjection() const {
        return mat4();
    }

    /**
     * Returns the matrix used to transform positions into position relative to the camera
     * position and rotation
     *
     * @return mat4 the transform matrix
     */
    const mat4 getViewMatrix() const {
        return mViewMatrix;
    }
};


class SceneObject {

private:
	static U32 sLastId;

    U32 mId;
    vector<SceneObject> mChildren;
    SceneObject *mParent {nullptr};
    
	GLModel *mModel {nullptr};

    vec3 mPosition;
    vec3 mRotation;
    vec3 mScale;
    mat4 mTransform;
    bool mDirty;

	/**
	 * Reset dirtyFlag to None
	 */
	void cleanDirtyFlag();

public:
	SceneObject() :
		mId(sLastId++),
		mDirty(true),
		mPosition(vec3(0.0f, 0.0f, 0.0f)),
		mRotation(vec3(0.0f, 0.0f, 0.0f)),
		mScale(vec3(1.0f, 1.0f, 1.0f)) {}
	~SceneObject() {}

	void setModel(GLModel* model);

	GLModel* getModel() const;


    vec3 getPosition() const;
    vec3 getRotation() const;
    vec3 getScale() const;
    void setPosition(const vec3 newPosition);
    void setRotation(const vec3 newRotation);
    void setScale(const vec3 newScale);
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void addX(float x);
    void addY(float y);
    void addZ(float z);
    float getX() const;
    float getY() const;
    float getZ() const;
    void setRotX(float x);
    void setRotY(float y);
    void setRotZ(float z);
    void addRotX(float x);
    void addRotY(float y);
    void addRotZ(float z);
    float getRotX() const;
    float getRotY() const;
    float getRotZ() const;
    void setScaleX(float x);
    void setScaleY(float y);
    void setScaleZ(float z);
    void addScaleX(float x);
    void addScaleY(float y);
    void addScaleZ(float z);
    float getScaleX() const;
    float getScaleY() const;
    float getScaleZ() const;

    const mat4 getTransform();
    bool isDirty();

    /**
     * Recursive method setting dirty flag for itself and all of its
     * children SceneObjects
     *
     * @param flag Flag to set
     */
    void setDirty();

    void draw();

	void appendChild(SceneObject obj);
};

}

#endif //GANESHENGINE_GHSCENEOBJECT_H
