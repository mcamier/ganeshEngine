#ifndef GANESHENGINE_GHGLPROGRAM_H
#define GANESHENGINE_GHGLPROGRAM_H

#include "ghHeaders.h"
#include <initializer_list>
#include <graphics/ghShader.h>

namespace ganeshEngine {

using namespace std;


class ShaderProgram {
    friend class Model;

private:
    GLProgramStatus mStatus;
    GLuint mInternalId;

public:
    ShaderProgram() : mStatus(GLProgramStatus::NONE), mInternalId(-1) {}

    ~ShaderProgram() {}

    template<typename... S>
    static ShaderProgram create(Shader &first, S &... rest) {
        ShaderProgram program = ShaderProgram();
        program.mInternalId = glCreateProgram();

        return ShaderProgram::create(program, first, rest...);
    }

    template<typename... F>
    static ShaderProgram create(ShaderType shaderType, const char *first, F... rest) {
        ShaderProgram program = ShaderProgram();
        program.mInternalId = glCreateProgram();

        return ShaderProgram::create(program, shaderType, first, rest...);
    }

    void logProgramInfo();

    void setUniform(const char *name, vec3 value);

    void setUniform(const char *name, vec4 value);

    void setUniform(const char *name, mat3 value);

    void setUniform(const char *name, mat4 value);

    bool sendToGC() const;

    bool freeFromGC() const;

private:
    template<typename... S>
    static ShaderProgram create(ShaderProgram &program, Shader &shader, S &... rest) {
        /// try to compile the shader if it is not already compiled
        if (shader.getStatus() == ShaderStatus::NONE) {
            shader.sendToGc();
        }
        /// check if shader compilation is successfull, fail creation if not
        if (shader.getStatus() != ShaderStatus::COMPILED) {
            throw std::exception();
        }
        glAttachShader(program.mInternalId, shader.mInternalId);
        ShaderProgram p = ShaderProgram::create(program, rest...);
        if (program.mStatus == GLProgramStatus::COMPILED) {
            glDetachShader(program.mInternalId, shader.mInternalId);
        }
        return program;
    }

    template<typename... F>
    static ShaderProgram create(ShaderProgram &program, ShaderType type, const char *filename, F... rest) {
        Shader *shader = Shader::fromFile(type, filename);
        shader->sendToGc();
        /// check if shader compilation is successfull, fail creation if not
        if (shader->getStatus() != ShaderStatus::COMPILED) {
            throw std::exception();
        }
        glAttachShader(program.mInternalId, shader->mInternalId);
        ShaderProgram p = ShaderProgram::create(program, rest...);
        if (program.mStatus == GLProgramStatus::COMPILED) {
            glDetachShader(program.mInternalId, shader->mInternalId);
        }
        return program;
    }

    static ShaderProgram create(ShaderProgram &program);

    void use();

    bool inUse();

    void stopUsing();
};

}

#endif //GANESHENGINE_GHGLPROGRAM_H
