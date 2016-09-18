#ifndef GANESHENGINE_GHICOMPONENT_H
#define GANESHENGINE_GHICOMPONENT_H

#include "ghHeaders.h"
#include "ghGameObject.h"
#include "ghClock.h"

#include <glm/glm.hpp>

using namespace glm;

namespace ganeshEngine {

//forward declaration
class Actor;

/**
 * Base class for all actor's component
 */
class Component : public GameObject {
    friend class Actor;

RTTI_DECL()

protected:
    bool mUpdateEnabled;

public:
    explicit Component(U32 id);
    explicit Component(U32 id, bool updateEnabled);

    /**
     * Call the component defined update method if the component currently allows update call
     *
     * @param clock clock
     */
    virtual void update(const Clock &clock);

protected:
    /**
     * Component defined update behavior
     *
     * @param clock clock
     */
    virtual void vUpdate(const Clock &clock) = 0;
};


/**
 * Base component for all component that could be located within the scene its owner belongs
 */
class SceneComponent : public Component {
    friend class Actor;

RTTI_DECL()

    bool mbDirty;

    float mPosX;
    float mPosY;
    float mPosZ;

    float mScaleX;
    float mScaleY;
    float mScaleZ;

    float mRotX;
    float mRotY;
    float mRotZ;


    float mWPosX;
    float mWPosY;
    float mWPosZ;

    float mWScaleX;
    float mWScaleY;
    float mWScaleZ;

    float mWRotX;
    float mWRotY;
    float mWRotZ;

protected:
    SceneComponent *mParentComponent;
    vector<Component *> mSubComponents;

public:
    explicit SceneComponent(U32 id);
    explicit SceneComponent(U32 id, bool updateEnabled);

    /**
     *
     * @param subComponent
     */
    void addSubComponent(Component * subComponent);

public:
    void update(const Clock &clock) override;

    void refresh();
    void setDirty();

    float getWorldPosX();
    float getWorldPosY();
    float getWorldPosZ();

    float getWorldRotX();
    float getWorldRotY();
    float getWorldRotZ();

    float getWorldScaleX();
    float getWorldScaleY();
    float getWorldScaleZ();

    float getPosX() const;
    void setPosX(float value);
    void addToPosX(float value);

    float getPosY() const;
    void setPosY(float value);
    void addToPosY(float value);

    float getPosZ() const;
    void setPosZ(float value);
    void addToPosZ(float value);

    float getRotX() const;
    void setRotX(float value);
    void addToRotX(float value);

    float getRotY() const;
    void setRotY(float value);
    void addToRotY(float value);

    float getRotZ() const;
    void setRotZ(float value);
    void addToRotZ(float value);

    float getScaleX() const;
    void setScaleX(float value);
    void addToScaleX(float value);

    float getScaleY() const;
    void setScaleY(float value);
    void addToScaleY(float value);

    float getScaleZ() const;
    void setScaleZ(float value);
    void addToScaleZ(float value);
};

}

#endif //GANESHENGINE_GHICOMPONENT_H
