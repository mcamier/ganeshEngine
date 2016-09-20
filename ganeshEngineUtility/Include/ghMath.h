#ifndef GHMATH_H
#define GHMATH_H

#include <vector>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

namespace ganeshEngine {

using namespace glm;
using namespace std;

// TODO lerp for quaternion

/**
 *
 * @param begin
 * @param end
 * @param t
 * @return
 */
template<typename T>
T lerp(T begin, T end, float t);

/**
 *
 * @param value
 * @return
 */
template<typename T>
T clamp01(T value) {
	if (value < 0.0f) {
		return 0.0f;
	}
	if (value > 1.0f) {
		return 1.0f;
	}
	return value;
}

/**
 *
 * @param pt1
 * @param pt2
 * @param pt3
 * @param t
 * @return
 */
vec3 quadraBezierPoint(vec3 pt1, vec3 pt2, vec3 pt3, float t);

/**
 *
 * @param pt1
 * @param pt2
 * @param pt3
 * @param t
 * @return
 */
vec3 quadraBezierFirstDerivative(vec3 pt1, vec3 pt2, vec3 pt3, float t);

/**
 *
 * @param pt1
 * @param pt2
 * @param pt3
 * @param pt4
 * @param t
 * @return
 */
vec3 cubicBezierPoint(vec3 pt1, vec3 pt2, vec3 pt3, vec3 pt4, float t);

/**
 *
 * @param pt1
 * @param pt2
 * @param pt3
 * @param pt4
 * @param t
 * @return
 */
vec3 cubicBezierFirstDerivative(vec3 pt1, vec3 pt2, vec3 pt3, vec3 pt4, float t);

/**
 */
class BezierSpline {
private:
	vector <vec3> points;

public:
	BezierSpline(vec3 pt1, vec3 pt2, vec3 pt3, vec3 pt4);

	virtual ~BezierSpline();

	void appendCurve(vec3 pt1, vec3 pt2, vec3 pt3);

	vec3 getValue(float t);

	vec3 getDirection(float t);

	int getCurveCount();

private:

	int getCurveIndex(float t);

	float getCurveT(float t);
};


}

#endif /* GHMATH_H */

