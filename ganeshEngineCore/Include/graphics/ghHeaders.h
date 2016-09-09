#ifndef GANESHENGINE_GRAPHICS_GHHEADERS_H
#define GANESHENGINE_GRAPHICS_GHHEADERS_H

#include "../ghHeaders.h"

namespace ganeshEngine {

using namespace std;
using namespace glm;

/*
const char *GL_type_to_string(GLenum type) {
    switch (type) {
        case GL_BOOL:
            return "bool";
        case GL_INT:
            return "int";
        case GL_FLOAT:
            return "float";
        case GL_FLOAT_VEC2:
            return "vec2";
        case GL_FLOAT_VEC3:
            return "vec3";
        case GL_FLOAT_VEC4:
            return "vec4";
        case GL_FLOAT_MAT2:
            return "mat2";
        case GL_FLOAT_MAT3:
            return "mat3";
        case GL_FLOAT_MAT4:
            return "mat4";
        case GL_SAMPLER_2D:
            return "sample2d";
        case GL_SAMPLER_3D:
            return "sample3d";
        case GL_SAMPLER_CUBE:
            return "sampleCube";
        case GL_SAMPLER_2D_SHADOW:
            return "sample2dShadow";
        default:
            return "other";
    }
}*/

/**
 * Defines shader's types supported by the engine
 */
enum class ShaderType : GLenum {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER,
};


/**
 * Defines shader's current status
 */
enum class ShaderStatus {
    NONE = 0x01,
    COMPILED = 0x02,
    FAILED = 0x03,
};

/**
 *
 */
enum class DrawMode : GLenum {
    POINTS = GL_POINTS,
    LINES = GL_LINES,
    LINE_STRIP = GL_LINE_STRIP,
    LINE_LOOP = GL_LINE_LOOP,
    TRIANGLES = GL_TRIANGLES,
    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    TRIANGLE_FAN = GL_TRIANGLE_FAN
};

/**
 *
 */
enum class AttribPointer : U32 {
    VERTEX = 0,
    COLOR = 1,
    UV = 2,
    NORMAL = 3

};

/**
 * Store each informations needed by a given vertex : its location in space
 * texture position, the normal and a color
 */
class Vertex {
public:
    F32 x, y, z;
    F32 r, g, b;
    F32 u, v;
    F32 nx, ny, nz;

    Vertex(F32 _x, F32 _y, F32 _z, F32 _u, F32 _v, F32 _nx, F32 _ny, F32 _nz) :
            x(_x), y(_y), z(_z), r(1.0f), g(1.0f), b(1.0f), u(0.0f), v(0.0f), nx(_nx), ny(ny), nz(_nz) {
    }

    Vertex(F32 _x, F32 _y, F32 _z, F32 _r, F32 _g, F32 _b, F32 _u, F32 _v, F32 _nx, F32 _ny, F32 _nz) :
            x(_x), y(_y), z(_z), r(_r), g(_g), b(_b), u(0.0f), v(0.0f), nx(_nx), ny(ny), nz(_nz) {
    }
};

/**
 *
 */
enum FrustumPlane {
    NEAR = 0,
    FAR = 1,
    BOTTOM = 2,
    TOP = 3,
    LEFT = 4,
    RIGHT = 5
};

/**
 *
 */
enum GLProgramStatus {
    NONE = 0b0001,
    COMPILED = 0b0010,
    FAILED = 0b0100
};

}

#endif //GANESHENGINE_GRAPHICS_GHHEADERS_H
