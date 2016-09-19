#ifndef GANESHENGINE_GHSCENECOMPONENT_H
#define GANESHENGINE_GHSCENECOMPONENT_H

#include "ghHeaders.h"
#include "ghGameObject.h"
#include "ghClock.h"

#include <glm/glm.hpp>

using namespace glm;

namespace ganeshEngine {

/**
 * Base component for all component that could be located within the scene its owner belongs
 * SceneComponent could aldo embed tree of sub components, which may, or not, depends of parent's component location if
 * parent's component is SceneComponent as well
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
	 * Add the given component as a sub component
	 * @param subComponent
	 */
	void addSubComponent(Component * subComponent);

public:
	/**
	 * Call the component custom vUpdate overloaded method, then call all sub component udpate method
	 * @param clock
	 */
	void update(const Clock &clock) override;

	/**
	 * Compute the world relative location, rotation and scale accordingly the component informations and parent
	 * component's information recursively
	 */
	void refresh();

	/**
	 * Set the component's flag as dirty, then do the same for all sub components which are also instances of
	 * SceneComponent
	 */
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

#endif //GANESHENGINE_GHSCENECOMPONENT_H
