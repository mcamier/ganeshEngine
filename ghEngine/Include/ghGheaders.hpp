#ifndef GANESHENGINE_GRAPHICS_GHHEADERS_H
#define GANESHENGINE_GRAPHICS_GHHEADERS_H

#include "ghHeaders.hpp"
#include <glm/glm.hpp>

namespace ganeshEngine {

using namespace std;
using namespace glm;

/**
 * Defines shader's types supported by the engine
enum class ShaderType : GLenum {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER,
};
 */
enum class ShaderType {
    VERTEX = 1,
    FRAGMENT = 2
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
enum class DrawMode : GLenum {
    POINTS = GL_POINTS,
    LINES = GL_LINES,
    LINE_STRIP = GL_LINE_STRIP,
    LINE_LOOP = GL_LINE_LOOP,
    TRIANGLES = GL_TRIANGLES,
    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    TRIANGLE_FAN = GL_TRIANGLE_FAN
};
 */
enum class DrawMode {
    POINTS = 1,
    LINES = 2,
    LINE_STRIP = 3,
    LINE_LOOP = 4,
    TRIANGLES = 5,
    TRIANGLE_STRIP = 6,
    TRIANGLE_FAN = 7
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

    explicit Vertex(vec3 point, vec3 color, vec2 uv, vec3 normal) :
            x(point.x), y(point.y), z(point.z),
            r(color.r), g(color.g), b(color.b),
            u(uv.x), v(uv.y),
            nx(normal.x), ny(normal.y), nz(normal.z) {
    }

    explicit Vertex(vec3 point, vec3 color, vec3 normal) :
            x(point.x), y(point.y), z(point.z),
            r(color.r), g(color.g), b(color.b),
            u(0.0f), v(0.0f),
            nx(normal.x), ny(normal.y), nz(normal.z) {
    }
};

/**
 *
 */
enum GLProgramStatus {
    NONE = 0x1,
    COMPILED = 0x2,
    FAILED = 0x3
};

}

#endif //GANESHENGINE_GRAPHICS_GHHEADERS_H
