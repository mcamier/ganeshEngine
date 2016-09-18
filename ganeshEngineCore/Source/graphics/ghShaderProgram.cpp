#include "graphics/ghShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

namespace ganeshEngine {

void ShaderProgram::use() const {
    glUseProgram(mInternalId);
}

bool ShaderProgram::inUse() const {
    GLint param = -1;
    glGetIntegerv(GL_CURRENT_PROGRAM, &param);
    return ((GLint) mInternalId == param);
}

void ShaderProgram::stopUsing() const {
    GLint param = -1;
    glGetIntegerv(GL_CURRENT_PROGRAM, &param);
    if ((GLint) mInternalId == param) {
        glUseProgram(0);
    }
}

bool ShaderProgram::sendToGc() {
    mInternalId = glCreateProgram();
    glAttachShader(mInternalId, mVertex->mInternalId);
    glAttachShader(mInternalId, mFragment->mInternalId);

    glLinkProgram(mInternalId);

    /// error checking
    int isLinked = 0;
    glGetProgramiv(mInternalId, GL_LINK_STATUS, &isLinked);
    if (isLinked != GL_TRUE) {
        GLint maxLength = 0;
        glGetProgramiv(mInternalId, GL_INFO_LOG_LENGTH, &maxLength);
        char *strInfoLog = new char[maxLength + 1];
        glGetProgramInfoLog(mInternalId, maxLength, nullptr, strInfoLog);
        strInfoLog[maxLength] = '\0';
        glDeleteProgram(mInternalId);
        _ERROR(strInfoLog, LOG_CHANNEL::RENDER);
        delete[] strInfoLog;
        //program.mStatus = GLProgramStatus::FAILED;

        return false;
    }
    int isValid = -1;
    glValidateProgram(mInternalId);
    glGetProgramiv(mInternalId, GL_VALIDATE_STATUS, &isValid);
    if (GL_TRUE != isValid) {
        //program.mStatus = GLProgramStatus::FAILED;
        int maxLength = 2048;
        int currentLength = 0;
        char log[maxLength];
        glGetProgramInfoLog(mInternalId, maxLength, &currentLength, log);
        _ERROR("Shader program failed to validate : " << log, LOG_CHANNEL::RENDER);

        return false;
    }

    return Resource::sendToGc();
}

bool ShaderProgram::freeFromGc() {
    Resource::freeFromGc();
    return true;
}


void ShaderProgram::logProgramInfo() {
    _DEBUG("Shader program infos : " << mInternalId, LOG_CHANNEL::DEFAULT);
    int params = -1;

    glGetProgramiv(mInternalId, GL_LINK_STATUS, &params);
    _DEBUG("\tGL_LINK_STATUS : " << params, LOG_CHANNEL::RENDER);

    glGetProgramiv(mInternalId, GL_ATTACHED_SHADERS, &params);
    _DEBUG("\tGL_ATTACHED_SHADERS : " << params, LOG_CHANNEL::RENDER);

    glGetProgramiv(mInternalId, GL_ACTIVE_ATTRIBUTES, &params);
    _DEBUG("\tGL_ACTIVE_ATTRIBUTES : " << params, LOG_CHANNEL::RENDER);
    for (GLuint i = 0; i < (GLuint) params; i++) {
        char name[64];
        int maxLenght = 64;
        int currentLenght = 0;
        int size = 0;
        GLenum type;

        glGetActiveAttrib(mInternalId, i, maxLenght, &currentLenght, &size, &type, name);
        if (size > 1) {
            for (int j = 0; j < size; j++) {
                char long_name[64];
                sprintf(long_name, "%s[%i]", name, j);
                //int location = glGetAttribLocation(mInternalId, long_name);
                //_DEBUG("\t\t" << i << "> type: " << glType2String(type) << " name: " << long_name << " location: " << location, LOG_CHANNEL::RENDER);
            }
        } else {
            //int location = glGetAttribLocation(mInternalId, name);
            //_DEBUG("\t\t" << i << "> type: " << glType2String(type) << " name: " << name << " location: " << location, LOG_CHANNEL::RENDER);
        }
    }

    glGetProgramiv(mInternalId, GL_ACTIVE_UNIFORMS, &params);
    _DEBUG("\tGL_ACTIVE_UNIFORMS : " << params, LOG_CHANNEL::RENDER);
    for (GLuint i = 0; i < (GLuint) params; i++) {
        char name[64];
        int maxLenght = 64;
        int currentLenght = 0;
        int size = 0;
        GLenum type;

        glGetActiveUniform(mInternalId, i, maxLenght, &currentLenght, &size, &type, name);
        if (size > 1) {
            for (int j = 0; j < size; j++) {
                char long_name[64];
                sprintf(long_name, "%s[%i]", name, j);
                //int location = glGetUniformLocation(mInternalId, long_name);
                //_DEBUG("\t\t" << i << "> type: " << glType2String(type) << " name: " << long_name << " location: " << location, LOG_CHANNEL::RENDER);
            }
        } else {
            //int location = glGetUniformLocation(mInternalId, name);
            //_DEBUG("\t\t" << i << "> type: " << glType2String(type) << " name: " << name << " location: " << location, LOG_CHANNEL::RENDER);
        }
    }

}

/*

void setUniform(const char *name, mat4 value) {
    GLint id = glGetUniformLocation(this->mInternalId, name);
    if (id != -1 && inUse()) {
        glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(value));
    }
}

void setUniform(const char *name, mat3 value) {
    GLint id = glGetUniformLocation(this->mInternalId, name);
    if (id != -1 && inUse()) {
        glUniformMatrix3fv(id, 1, GL_FALSE, glm::value_ptr(value));
    }
}

void setUniform(const char *name, vec3 value) {
    GLint id = glGetUniformLocation(this->mInternalId, name);
    if (id != -1 && inUse()) {
        glUniform3fv(id, 1, glm::value_ptr(value));
    }
}

void setUniform(const char *name, vec4 value) {
    GLint id = glGetUniformLocation(this->mInternalId, name);
    if (id != -1 && inUse()) {
        glUniform4fv(id, 1, glm::value_ptr(value));
    }
}
     */

}