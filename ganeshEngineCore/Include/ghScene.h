#ifndef GANESHENGINE_GHSCENE_H
#define GANESHENGINE_GHSCENE_H

#include "ghHeaders.h"

namespace ganeshEngine {

using namespace std;

/**
 *
 */
enum DirtyFlag{
    NONE        = 0x00,
    POSITION    = 0x01,
    ROTATION    = 0x02,
    SCALE       = 0x04,
};


/**
 *
 */
class SceneObject {

private:
    U32 mId;
    vector<SceneObject*> mChildren;
    SceneObject* mParent;

    vector3f mPosition;
    vector3f mRotation;
    vector3f mScale;

    DirtyFlag mDirty;

    /** Reset dirtyFlag to None
     */
    void cleanDirtyFlag();

    /** Recursive method setting dirty flag for itself and all of its
     *  children SceneObjects
     */
    void setDirty(DirtyFlag flag);


public:
    bool isDirty();

};


/**
 *
 */
class Scene {

private:
    SceneObject *mRoot;


};


}

#endif //GANESHENGINE_GHSCENE_H
