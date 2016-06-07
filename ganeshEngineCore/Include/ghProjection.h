#ifndef GANESHENGINE_GHPERSPECTIVE_H
#define GANESHENGINE_GHPERSPECTIVE_H

#include "ghHeaders.h"
#include <glm/glm.hpp>

namespace ganeshEngine {

using namespace glm;

class IProjection {

public:
	virtual const mat4& vTransform() const = 0;
};


class OrthogonalProjection : public IProjection {

private:
	mat4 mTransformation;
	float mNear;
	float mFar;
	float mTop;
	float mBottom;
	float mRight;
	float mLeft;

public:
	OrthogonalProjection(float near,float far,float top,float bottom,float left,float right) :
			mNear(near), mFar(far), mTop(top), mBottom(bottom), mLeft(left), mRight(right) {
		updateInternal();
	}
	~OrthogonalProjection();

	const mat4& vTransform() const override {
		return mTransformation;
	}

protected:
	void updateInternal() {
		mTransformation[0][0] = 2.0f / (mRight-mLeft);
		mTransformation[0][1] = 0.0f;
		mTransformation[0][2] = 0.0f;
		mTransformation[0][3] = 0.0f;

		mTransformation[1][0] = 0.0f;
		mTransformation[1][1] = 2.0f / (mTop-mBottom);
		mTransformation[1][2] = 0.0f;
		mTransformation[1][3] = 0.0f;

		mTransformation[2][0] = 0.0f;
		mTransformation[2][1] = 0.0f;
		mTransformation[2][2] = -1.0f / (mFar-mNear);
		mTransformation[2][3] = 0.0f;

		mTransformation[3][0] = -(mRight+mLeft)/(mRight-mLeft);
		mTransformation[3][1] = -(mTop+mBottom)/(mTop-mBottom);
		mTransformation[3][2] = -mNear / (mFar-mNear);
		mTransformation[3][3] = 1.0f;
	}
};


class PerspectiveProjection : public IProjection {

private:
	mat4 mTransformation;

public:
	PerspectiveProjection() {}
	~PerspectiveProjection();

	const mat4& vTransform() const override {
		return mTransformation;
	}

protected:
	void updateInternal() {}
};


}

#endif //GANESHENGINE_GHPERSPECTIVE_H
