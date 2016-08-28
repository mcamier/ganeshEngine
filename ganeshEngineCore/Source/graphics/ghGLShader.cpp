#include "graphics/ghGLShader.h"

#include "graphics/ghGLProgram.h"
#include <fstream>
#include <ghLoggerManager.h>

namespace ganeshEngine {

GLShader* GLShader::fromFile(ShaderType type, const char *filename) {
    std::ifstream t(filename);
    std::string content;

    t.seekg(0, std::ios::end);
    content.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    content.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    return new GLShader(type, content);
}

bool GLShader::sendToGc() {
    GLuint shaderId = glCreateShader((GLenum) mType);
    const char *content = mSource.c_str();
    glShaderSource(shaderId, 1, (const GLchar **) &content, nullptr);
    glCompileShader(shaderId);

    /** error check */
    GLint isCompiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
        char *strInfoLog = new char[maxLength + 1];
        glGetShaderInfoLog(shaderId, maxLength, nullptr, strInfoLog);
        strInfoLog[maxLength] = '\0';
        glDeleteShader(shaderId);
        _ERROR(strInfoLog, LOG_CHANNEL::RENDER);
        delete[] strInfoLog;
        mStatus = ShaderStatus::FAILED;

        return false;
    } else if (isCompiled == GL_TRUE) {
        mStatus = ShaderStatus::COMPILED;
    }
    mInternalId = shaderId;

    return true;
}

bool GLShader::freeFromGc() {
    // TODO
    return true;
}

const ShaderType GLShader::getType() const {
    return mType;
}

const ShaderStatus GLShader::getStatus() const {
    return mStatus;
}

}