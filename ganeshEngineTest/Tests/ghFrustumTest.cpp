#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "graphics/ghFrustum.h"

using namespace ganeshEngine;
using namespace glm;

class FrustumTest : public ::testing::Test {

protected:
	Frustum *frustum;

	FrustumTest() {
		frustum = new Frustum(16.0f/9.0f, 90, 1.0f, 1000.0f);
	}
};

TEST_F(FrustumTest, pointShouldBeInsideFrustum) {
	EXPECT_EQ(frustum->vIsColliding(vec3(0.0f, 0.0f, 50.0f)), true);
}

TEST_F(FrustumTest, pointShouldBeOutsideFrustum) {
	EXPECT_EQ(frustum->vIsColliding(vec3(-999.0f, -999.0f, -999.0f)), false);
}
