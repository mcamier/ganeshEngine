#ifndef GANESHENGINE_GHSCENEOBJECT_H
#define GANESHENGINE_GHSCENEOBJECT_H

#include "ghHeaders.h"

namespace ganeshEngine {

    using namespace glm;
    using namespace std;

    class Scene;

    enum class SceneObjectType {
        ACTOR,
        CAMERA,
        LIGHT,
        SKYBOX
    };

/**
 *
 */
    class SceneObject {
        friend class Scene;

/*TODO limit the scope to private for some or all members */
    protected:
        U32 mId;
        const SceneObjectType mType;
        bool mDirty;

        vec3 mPosition;
        vec3 mRotation;
        vec3 mScale;

        vector<SceneObject *> mChildren;
        SceneObject *mParent{nullptr};

        Scene *mOwner{nullptr};

        mat4 mTransform;

        static U32 sLastId;

        /**
         * Reset dirtyFlag to None
         */
        void cleanDirtyFlag();

    public:
        SceneObject(SceneObjectType type) :
                mId(sLastId++),
                mType(type),
                mDirty(true),
                mPosition(vec3(0.0f, 0.0f, 0.0f)),
                mRotation(vec3(0.0f, 0.0f, 0.0f)),
                mScale(vec3(1.0f, 1.0f, 1.0f)),
                mChildren(vector<SceneObject *>()),
                mParent(nullptr),
                mOwner(nullptr),
                mTransform(mat4()) {}

        virtual ~SceneObject() {}

        const mat4 getTransform();

        bool isDirty();

        /**
         * Recursive method setting dirty flag for itself and all of its
         * children SceneObjects
         *
         * @param flag Flag to set
         */
        void setDirty();

        virtual void preRender();

        virtual void render();

        virtual void postRender();

        void appendChild(SceneObject *obj);

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

    private:
        void setOwner(Scene *owner);
    };

}

#endif //GANESHENGINE_GHSCENEOBJECT_H
