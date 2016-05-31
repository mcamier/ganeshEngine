#include "ghScene.h"

namespace ganeshEngine {

    void SceneObject::cleanDirtyFlag() {
        mDirty = DirtyFlag.NONE;
    }

    void SceneObject::setDirty(DirtyFlag flag) {
        mDirty |= flag;
        if(mChildren.size() > 0) {
            for(auto child : mChildren) {
                child->setDirty(flag);
            }
        }
    }

    bool SceneObject::isDirty() {
        return (mDirty() & DirtyFlag.NONE) != DirtyFlag.NONE;
    }

}