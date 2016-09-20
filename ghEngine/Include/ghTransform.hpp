#ifndef GANESHENGINE_GHTRANSFORM_H
#define GANESHENGINE_GHTRANSFORM_H

#include <glm/glm.hpp>

using namespace glm;

namespace ganeshEngine {

class Transform {
private:
	mat4 mmMatrix;

	vec3 mLocation;
	vec3 mRotation;
	vec3 mScale;

	bool mbDirty;

public:
	Transform();
	~Transform();

	void refresh();

	vec3 getPos() const;
	vec3 getRotation() const;
	vec3 getScale() const;

	void setPos(const vec3 newPosition);
	void setRotation(const vec3 newRotation);
	void setScale(const vec3 newScale);

	float getPosX() const;
	float getPosY() const;
	float getPosZ() const;

	void setPosX(float value);
	void setPosY(float value);
	void setPosZ(float value);

	void addToPosX(float value);
	void addToPosY(float value);
	void addToPosZ(float value);


	float getRotX() const;
	float getRotY() const;
	float getRotZ() const;

	void setRotY(float value);
	void setRotX(float value);
	void setRotZ(float value);

	void addToRotX(float value);
	void addToRotY(float value);
	void addToRotZ(float value);


	float getScaleX() const;
	float getScaleY() const;
	float getScaleZ() const;

	void setScaleX(float value);
	void setScaleY(float value);
	void setScaleZ(float value);

	void addToScaleX(float value);
	void addToScaleY(float value);
	void addToScaleZ(float value);
};

}

#endif //GANESHENGINE_GHTRANSFORM_H
