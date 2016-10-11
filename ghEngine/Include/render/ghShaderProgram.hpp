#ifndef GANESHENGINE_GHGLPROGRAM_H
#define GANESHENGINE_GHGLPROGRAM_H



#include "ghShader.hpp"
#include "resource/ghResourceHandler.hpp"

#include <initializer_list>
#include <glm/gtc/type_ptr.hpp>


namespace ganeshEngine {

using namespace std;

/*const char *glType2String(GLenum type) {
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

class ShaderProgram : public Resource {
    friend class ShaderProgramLoader;

private:
    ResourceHandler<Shader> mVertex;
    ResourceHandler<Shader> mFragment;

    /** opengl internal id */
    //GLuint mInternalId;
    int mInternalId;

public:
    ShaderProgram(ResourceHandler<Shader> vertex, ResourceHandler<Shader> fragment) :
            Resource(),
            mVertex(vertex),
            mFragment(fragment),
            mInternalId(-1) {}

    ~ShaderProgram() {}

    void use() const;

    bool inUse() const;

    void stopUsing() const;

    void logProgramInfo();
    /*
    void setUniform(const char *name, mat4 value);
    void setUniform(const char *name, mat3 value);
    void setUniform(const char *name, vec3 value);
    void setUniform(const char *name, vec4 value);
     */
};

}

#endif //GANESHENGINE_GHGLPROGRAM_H
