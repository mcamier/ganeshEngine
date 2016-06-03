#include <gtest/gtest.h>
#include "ghPlane.h"
#include <glm/glm.hpp>
#include <iostream>

using namespace ganeshEngine;
using namespace glm;
using namespace std;

class PlaneTest : public ::testing::Test {

protected:
	Plane *poly;
	Plane *otherPoly;

	PlaneTest() {
		poly = new Plane(vec3(0.0f, 0.0f, 0.0f), vec3(10.0f, 0.0f, 0.0f), vec3(10.0f, 10.0f, 0.0f));
		otherPoly = new Plane(vec3(10.0f, 10.0f, 0.0f), vec3(10.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f));
	}
};

TEST_F(PlaneTest, normalShouldHeadsForward) {
	EXPECT_EQ(poly->getNormal(), vec3(0.0f, 0.0f, 1.0f));
}

TEST_F(PlaneTest, normalShouldHeadsBackward) {
	EXPECT_EQ(otherPoly->getNormal(), vec3(0.0f, 0.0f, -1.0f));
}

TEST_F(PlaneTest, pointShouldBeInFrontOfPlane) {
	EXPECT_EQ(poly->isToward(vec3(10.0f, 23.0f, 38.0f)), true);
}

TEST_F(PlaneTest, pointShouldBeBehindOfPlane) {
	EXPECT_EQ(poly->isToward(vec3(80.0f, 12.0f, -23.0f)), false);
}