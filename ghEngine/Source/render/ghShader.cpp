#include "render/ghShader.hpp"

#include "render/ghShaderProgram.hpp"
#include <fstream>
#include "util/ghLoggerManager.hpp"

namespace ganeshEngine {

    /*
    GLuint shaderId = glCreateShader((GLenum) mType);
    const char *content = mSource.c_str();
    glShaderSource(shaderId, 1, (const GLchar **) &content, nullptr);
    glCompileShader(shaderId);

    // error check
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

        return false;
    }

    mInternalId = shaderId;
*/


const ShaderType Shader::getType() const {
    return mType;
}

}