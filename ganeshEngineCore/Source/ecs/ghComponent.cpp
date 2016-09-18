#include <ecs/ghBoxColliderComponent.h>
#include "ecs/ghIComponent.h"

#include "ecs/ghActor.h"
#include "ghClock.h"

namespace ganeshEngine {

Component::Component(U32 id) :
        GameObject(id),
        mUpdateEnabled(true) {}

Component::Component(U32 id, bool updateEnabled) :
        GameObject(id),
        mUpdateEnabled(updateEnabled) {}

void Component::update(const Clock &clock) {
    if (mUpdateEnabled)
        vUpdate(clock);
}


SceneComponent::SceneComponent(U32 id) :
        Component(id),
        mbDirty(true),
        mPosX(.0), mPosY(.0), mPosZ(.0),
        mScaleX(.0), mScaleY(.0), mScaleZ(.0),
        mRotX(.0), mRotY(.0), mRotZ(.0),
        mWPosX(.0), mWPosY(.0), mWPosZ(.0),
        mWScaleX(.0), mWScaleY(.0), mWScaleZ(.0),
        mWRotX(.0), mWRotY(.0), mWRotZ(.0),
        mParentComponent(nullptr),
        mSubComponents(vector<Component*>()) {}

SceneComponent::SceneComponent(U32 id, bool updateEnabled) :
        Component(id, updateEnabled),
        mbDirty(true),
        mPosX(.0), mPosY(.0), mPosZ(.0),
        mScaleX(.0), mScaleY(.0), mScaleZ(.0),
        mRotX(.0), mRotY(.0), mRotZ(.0),
        mWPosX(.0), mWPosY(.0), mWPosZ(.0),
        mWScaleX(.0), mWScaleY(.0), mWScaleZ(.0),
        mWRotX(.0), mWRotY(.0), mWRotZ(.0),
        mParentComponent(nullptr),
        mSubComponents(vector<Component*>()){}


void SceneComponent::update(const Clock &clock) {
    Component::update(clock);

    for(Component* subComponent: mSubComponents)
        subComponent->update(clock);
}

void SceneComponent::addSubComponent(Component * subComponent) {
    mSubComponents.push_back(subComponent);
    if(subComponent->getRTTI().isDerivedFrom(SceneComponent::rtti)) {
        ((SceneComponent*)subComponent)->mParentComponent = this;
    }
}

float SceneComponent::getPosX()  const{
    return mPosX;
}

void SceneComponent::setPosX(float value) {
    setDirty();
    mPosX = value;
}

void SceneComponent::addToPosX(float value) {
    setDirty();
    mPosX += value;
}

float SceneComponent::getPosY() const {
    return mPosY;
}

void SceneComponent::setPosY(float value) {
    setDirty();
    mPosY = value;
}

void SceneComponent::addToPosY(float value) {
    setDirty();
    mPosY += value;
}

float SceneComponent::getPosZ() const {
    return mPosZ;
}

void SceneComponent::setPosZ(float value) {
    setDirty();
    mPosZ = value;
}

void SceneComponent::addToPosZ(float value) {
    setDirty();
    mPosZ += value;
}

float SceneComponent::getRotX() const {
    return mRotX;
}

void SceneComponent::setRotX(float value) {
    setDirty();
    mRotX = value;
}

void SceneComponent::addToRotX(float value) {
    setDirty();
    mRotX += value;
}

float SceneComponent::getRotY() const {
    return mRotY;
}

void SceneComponent::setRotY(float value) {
    setDirty();
    mRotY = value;
}

void SceneComponent::addToRotY(float value) {
    setDirty();
    mRotY += value;
}

float SceneComponent::getRotZ() const {
    return mRotZ;
}

void SceneComponent::setRotZ(float value) {
    setDirty();
    mRotZ = value;
}

void SceneComponent::addToRotZ(float value) {
    setDirty();
    mRotZ += value;
}

float SceneComponent::getScaleX() const {
    return mScaleX;
}

void SceneComponent::setScaleX(float value) {
    setDirty();
    mScaleX = value;
}

void SceneComponent::addToScaleX(float value) {
    setDirty();
    mScaleX += value;
}

float SceneComponent::getScaleY() const {
    return mScaleY;
}

void SceneComponent::setScaleY(float value) {
    setDirty();
    mScaleY = value;
}

void SceneComponent::addToScaleY(float value) {
    setDirty();
    mScaleY += value;
}

float SceneComponent::getScaleZ() const {
    return mScaleZ;
}

void SceneComponent::setScaleZ(float value) {
    setDirty();
    mScaleZ = value;
}

void SceneComponent::addToScaleZ(float value) {
    setDirty();
    mScaleZ += value;
}

float SceneComponent::getWorldPosX() {
    refresh();
    return mWPosX;
}

float SceneComponent::getWorldPosY() {
    refresh();
    return mWPosY;
}

float SceneComponent::getWorldPosZ() {
    refresh();
    return mWPosZ;
}

float SceneComponent::getWorldRotX() {
    refresh();
    return mWRotX;
}

float SceneComponent::getWorldRotY() {
    refresh();
    return mWRotY;
}

float SceneComponent::getWorldRotZ() {
    refresh();
    return mWRotZ;
}

float SceneComponent::getWorldScaleX() {
    refresh();
    return mWScaleX;
}

float SceneComponent::getWorldScaleY() {
    refresh();
    return mWScaleY;
}

float SceneComponent::getWorldScaleZ() {
    refresh();
    return mWScaleZ;
}

void SceneComponent::setDirty() {
    mbDirty = true;
    for(Component* subComponent : mSubComponents) {
        if(subComponent->getRTTI().isSame(SceneComponent::rtti)) {
            ((SceneComponent*)subComponent)->setDirty();
        }
    }
}

void SceneComponent::refresh() {
    if(mbDirty) {
        mbDirty = false;
        if(mParentComponent != nullptr) {
            mWPosX = mPosX + mParentComponent->getWorldPosX();
            mWPosY = mPosY + mParentComponent->getWorldPosY();
            mWPosZ = mPosZ + mParentComponent->getWorldPosZ();

            mWScaleX = mScaleX + mParentComponent->getWorldScaleX();
            mWScaleY = mScaleY + mParentComponent->getWorldScaleY();
            mWScaleZ = mScaleZ + mParentComponent->getWorldScaleZ();

            mWRotX = mRotX + mParentComponent->getWorldRotX();
            mWRotY = mRotY + mParentComponent->getWorldRotY();
            mWRotZ = mRotZ + mParentComponent->getWorldRotZ();
        } else {
            mWPosX = mPosX;
            mWPosY = mPosY;
            mWPosZ = mPosZ;

            mWScaleX = mScaleX;
            mWScaleY = mScaleY;
            mWScaleZ = mScaleZ;

            mWRotX = mRotX;
            mWRotY = mRotY;
            mWRotZ = mRotZ;
        }
    }
}

}
