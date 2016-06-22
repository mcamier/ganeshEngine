#include "ghSceneObject.h"

namespace ganeshEngine {

    U32 SceneObject::sLastId = 0;

    void SceneObject::setDirty() {
        mDirty = true;
        for(SceneObject child : mChildren) {
            /* Invalidate computed transform matrix of each children of this node */
            child.setDirty();
        }
    }

    void SceneObject::draw() {
        mModel->preRender();
        mModel->getProgram()->setUniform("gh_u_modelview_mat", this->getTransform());
        //mModel->getProgram()->setUniform("gh_u_camera_mat", camera);
        mModel->render();
        mModel->postRender();

        for (SceneObject child : mChildren) {
            child.draw();
        }
    }

    bool SceneObject::isDirty() {
        return mDirty;
    }

    void SceneObject::setModel(GLModel *model) {
        mModel = model;
    }

    GLModel* SceneObject::getModel() const {
        return mModel;
    }

    void SceneObject::cleanDirtyFlag() {
        mDirty = false;
    }

    const mat4 SceneObject::getTransform() {
        if(mDirty) {
            mat4 temp = mat4();
            mTransform = mat4();
            /*translation*/
            mTransform[3][0] = mPosition.x;
            mTransform[3][1] = mPosition.y;
            mTransform[3][2] = mPosition.z;

            /*scale*/
            temp[0][0] = mScale.x;
            temp[1][1] = mScale.y;
            temp[2][2] = mScale.z;
            mTransform = temp * mTransform;

            if(mParent != nullptr) {
                /* might cause calculation of parent's transform matrix recursively until parent without dirt flag */
                mTransform = mParent->getTransform() * mTransform;
            }
            cleanDirtyFlag();
        }
        return mTransform;
    }

    void SceneObject::setX(float x) {
        mPosition.x = x;
        setDirty();
    }

    void SceneObject::setY(float y) {
        mPosition.y = y;
        setDirty();
    }

    void SceneObject::setZ(float z) {
        mPosition.z = z;
        setDirty();
    }

    void SceneObject::addX(float x) {
        mPosition.x += x;
        setDirty();
    }

    void SceneObject::addY(float y) {
        mPosition.y += y;
        setDirty();
    }

    void SceneObject::addZ(float z) {
        mPosition.z += z;
        setDirty();
    }

    float SceneObject::getX() const { return mPosition.x; }
    float SceneObject::getY() const { return mPosition.y; }
    float SceneObject::getZ() const { return mPosition.z; }


    void SceneObject::setRotX(float x) {
        mRotation.x = x;
        setDirty();
    }

    void SceneObject::setRotY(float y) {
        mRotation.y = y;
        setDirty();
    }

    void SceneObject::setRotZ(float z) {
        mRotation.z = z;
        setDirty();
    }

    void SceneObject::addRotX(float x) {
        mRotation.x += x;
        setDirty();
    }

    void SceneObject::addRotY(float y) {
        mRotation.y += y;
        setDirty();
    }

    void SceneObject::addRotZ(float z) {
        mRotation.z += z;
        setDirty();
    }

    float SceneObject::getRotX() const { return mRotation.x; }
    float SceneObject::getRotY() const { return mRotation.y; }
    float SceneObject::getRotZ() const { return mRotation.z; }


    void SceneObject::setScaleX(float x) {
        mScale.x = x;
        setDirty();
    }

    void SceneObject::setScaleY(float y) {
        mScale.y = y;
        setDirty();
    }

    void SceneObject::setScaleZ(float z) {
        mScale.z = z;
        setDirty();
    }

    void SceneObject::addScaleX(float x) {
        mScale.x += x;
        setDirty();
    }

    void SceneObject::addScaleY(float y) {
        mScale.y += y;
        setDirty();
    }

    void SceneObject::addScaleZ(float z) {
        mScale.z += z;
        setDirty();
    }

    float SceneObject::getScaleX() const { return mScale.x; }
    float SceneObject::getScaleY() const { return mScale.y; }
    float SceneObject::getScaleZ() const { return mScale.z; }


    vec3 getPosition() const {
        return mPosition;
    }

    vec3 getRotation() const {
        return mRotation;
    }

    vec3 getScale() const {
        return mScale;
    }

    void setPosition(const vec3 newPosition) {
        mPosition = newPosition;
    }
    void setRotation(const vec3 newRotation) {
        mRotation = newRotation;
    }

    void setScale(const vec3 newScale) {
        mRotation = newRotation;
    }

    void SceneObject::appendChild(SceneObject obj) {
        obj.mParent = this;
        mChildren.push_back(obj);
    }
}