#include "ghFrustum.h"

#include <gtest/gtest.h>
#include <glm/glm.hpp>

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
	EXPECT_EQ(frustum->vIsColliding(vec3(-4.0f, 2.0f, 2.0f)), true);
}

TEST_F(FrustumTest, pointShouldBeOutsideFrustum) {
	EXPECT_EQ(frustum->vIsColliding(vec3(9999.0f, 9999.0f, 9999.0f)), false);
}
