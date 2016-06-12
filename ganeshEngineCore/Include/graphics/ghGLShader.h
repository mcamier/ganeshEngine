#ifndef GANESHENGINE_GHSHADER_H
#define GANESHENGINE_GHSHADER_H

#include "../ghHeaders.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ganeshEngine {

using namespace std;

class GLProgram;

/**
 * Defines shader's types supported by the engine
 */
enum class ShaderType : GLenum {
	VERTEX      = GL_VERTEX_SHADER,
	FRAGMENT    = GL_FRAGMENT_SHADER,
};


/**
 * Defines shader's current status
 */
enum class ShaderStatus {
	NONE        = 0x01,
	COMPILED    = 0x02,
	FAILED      = 0x04,
};


class GLShader {
	friend class GLProgram;

private:
	/**
	 * This id comes from opengl once the shader was created on GC
	 */
	GLuint mInternalId;

	/**
	 * The shader's type
	 */
    ShaderType mType;

	/**
	 * The shader's status
	 * After creation its value is NONE, should be COMPILED after a successful call
	 * to doCompile, FAILED oterwise
	 */
	ShaderStatus mStatus;

	/**
	 * The source of the shader
	 */
	string mSource;

public:
	GLShader(ShaderType type, string source) : mInternalId(-1), mType(type), mStatus(ShaderStatus::NONE), mSource(source) {}
	~GLShader() {}

	/**
	 *
	 * @param type
	 * @param filename
	 * @return Instance of GLShader
	 */
    static GLShader fromFile(ShaderType type, const char *filename);

	/**
	 *
	 */
	void doCompile();

	/**
	 *
	 * @return shader's type
	 */
	const ShaderType getType() const;

	/**
	 *
	 * @return shader's status
	 */
	const ShaderStatus getStatus() const;
};



}

#endif //GANESHENGINE_GHSHADER_H
