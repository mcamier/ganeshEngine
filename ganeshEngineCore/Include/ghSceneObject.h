#ifndef GANESHENGINE_GHSCENEOBJECT_H
#define GANESHENGINE_GHSCENEOBJECT_H

#include "ghHeaders.h"
#include "graphics/ghGLModel.h"

namespace ganeshEngine {

class SceneObject {

private:
	static U32 sLastId;

    U32 mId;
    vector<SceneObject> mChildren;
    SceneObject *mParent{nullptr};
    
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
