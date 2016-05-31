#ifndef GANESHENGINE_GHSHADER_H
#define GANESHENGINE_GHSHADER_H

#include "../ghHeaders.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ganeshEngine {

using namespace std;

class GLProgram;

/// Defines shader's types supported by the engine
enum class ShaderType : GLenum {
	VERTEX      = GL_VERTEX_SHADER,
	FRAGMENT    = GL_FRAGMENT_SHADER,
};


/// Defines shader's types supported by the engine
enum class ShaderStatus {
	NONE        = 0x01,
	COMPILED    = 0x02,
	FAILED      = 0x04,
};


class GLShader {
	friend class GLProgram;

private:
	GLuint mInternalId;
    ShaderType mType;
    ShaderStatus mStatus;
	string mSource;

public:
    GLShader(ShaderType type, string source) : mInternalId(-1), mType(type), mStatus(ShaderStatus::NONE), mSource(source) {}
    ~GLShader() {}

    static GLShader fromFile(ShaderType type, const char *filename);

	void doCompile();

	const ShaderType getType() const;

	const ShaderStatus getStatus() const;

};



}

#endif //GANESHENGINE_GHSHADER_H
