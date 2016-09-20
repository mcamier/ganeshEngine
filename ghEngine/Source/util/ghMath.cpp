#include "util/ghMath.hpp"

namespace ganeshEngine {

    using namespace std;
    using namespace glm;

    template<>
    float lerp<float>(float begin, float end, float t) {
        return (1 - t) * begin + t * end;
    }

    template<>
    double lerp<double>(double begin, double end, float t) {
        return (1 - t) * begin + t * end;
    }

    template<>
    vec2 lerp<vec2>(vec2 begin, vec2 end, float t) {
        vec2 result;
        result.x = (1 - t) * begin.x + t * end.x;
        result.y = (1 - t) * begin.y + t * end.y;
        return result;
    }

    template<>
    vec3 lerp<vec3>(vec3 begin, vec3 end, float t) {
        vec3 result;
        result.x = (1 - t) * begin.x + t * end.x;
        result.y = (1 - t) * begin.y + t * end.y;
        result.z = (1 - t) * begin.z + t * end.z;
        return result;
    }

    vec3 quadraBezierPoint(vec3 pt1, vec3 pt2, vec3 pt3, float t) {
        t = clamp01(t);
        float d = 1.0f - t;
        float dd = d * d;

        return dd * pt1 + 2.0f * d * t * pt2 + t * t * pt3;
    }

    vec3 quadraBezierFirstDerivative(vec3 pt1, vec3 pt2, vec3 pt3, float t) {
        return 2.0f * (1.0f - t) * (pt2 - pt1) + 2.0f * t * (pt3 - pt2);
    }

    vec3 cubicBezierPoint(vec3 pt1, vec3 pt2, vec3 pt3, vec3 pt4, float t) {
        t = clamp01(t);
        float ttt = t * t * t;
        float d = 1.0f - t;
        float ddd = d * d * d;
        float dd = d * d * d;

        return ddd * pt1 + 3.0f * dd * t * pt2 + 3.0f * d * t * t * pt3 + ttt * pt4;
    }

    vec3 cubicBezierFirstDerivative(vec3 pt1, vec3 pt2, vec3 pt3, vec3 pt4, float t) {
        float d = (1.0f - t);
        float dd = d * d;
        return 3.0f * dd * (pt2 - pt1) + 6.0f * d * t * (pt3 - pt2) + 3.0f * t * t * (pt4 - pt3);
    }

    BezierSpline::BezierSpline(vec3 pt1, vec3 pt2, vec3 pt3, vec3 pt4) {
        points.push_back(pt1);
        points.push_back(pt2);
        points.push_back(pt3);
        points.push_back(pt4);
    }

    BezierSpline::~BezierSpline() {
    }

    void BezierSpline::appendCurve(vec3 pt1, vec3 pt2, vec3 pt3) {
        points.push_back(pt1);
        points.push_back(pt2);
        points.push_back(pt3);
    }

    vec3 BezierSpline::getValue(float t) {
        int i = getCurveIndex(t);
        t = getCurveT(t);
        return cubicBezierPoint(
                points.at(i),
                points.at(i + 1),
                points.at(i + 2),
                points.at(i + 3),
                t);
    }

    vec3 BezierSpline::getDirection(float t) {
        int i = getCurveIndex(t);
        t = getCurveT(t);
        return normalize(cubicBezierFirstDerivative(
                points.at(i),
                points.at(i + 1),
                points.at(i + 2),
                points.at(i + 3),
                t));
    }

    int BezierSpline::getCurveCount() {
        return (points.size() - 1) / 3;
    }

    int BezierSpline::getCurveIndex(float t) {
        int i;
        if (t >= 1.0f) {
            return points.size() - 4;
        } else {
            i = (int) (clamp01(t) * getCurveCount());
            return i * 3;
        }
    }

    float BezierSpline::getCurveT(float t) {
        if (t >= 1.0f) {
            return 1.0f;
        }
        return clamp01(t) * getCurveCount();
    }

}