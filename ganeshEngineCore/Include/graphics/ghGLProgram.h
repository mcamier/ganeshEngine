#ifndef GANESHENGINE_GHGLPROGRAM_H
#define GANESHENGINE_GHGLPROGRAM_H

#include <initializer_list>
#include <graphics/ghGLShader.h>

namespace ganeshEngine {

using namespace std;

enum GLProgramStatus {
	NONE        = 0x01,
	COMPILED    = 0x02,
	FAILED      = 0x04,
};


class GLProgram {
	friend class GLModel;

private:
	GLProgramStatus mStatus;
	GLuint mInternalId;

public:
	GLProgram() : mStatus(GLProgramStatus::NONE), mInternalId(-1) {}
	~GLProgram() {}

	template<typename... S>
	static GLProgram create(GLShader& first, S&... rest) {
		GLProgram program = GLProgram();
		program.mInternalId = glCreateProgram();

		return GLProgram::create(program, first, rest...);
	}

	template<typename... F>
	static GLProgram create(ShaderType shaderType, const char *first, F... rest) {
		GLProgram program = GLProgram();
		program.mInternalId = glCreateProgram();

		return GLProgram::create(program, shaderType, first, rest...);
	}

	void logProgramInfo();

private:
	template<typename... S>
	static GLProgram create(GLProgram& program, GLShader& shader, S&... rest) {
		/// try to compile the shader if it is not already compiled
		if(shader.getStatus() == ShaderStatus::NONE) {
			shader.doCompile();
		}
		/// check if shader compilation is successfull, fail creation if not
		if(shader.getStatus() != ShaderStatus::COMPILED) {
			throw std::exception();
		}
		glAttachShader(program.mInternalId, shader.mInternalId);
		GLProgram p = GLProgram::create(program, rest...);
		if(program.mStatus == GLProgramStatus::COMPILED) {
			glDetachShader(program.mInternalId, shader.mInternalId);
		}
		return program;
	}

	template<typename... F>
	static GLProgram create(GLProgram& program, ShaderType type, const char *filename, F... rest) {
		GLShader shader = GLShader::fromFile(type, filename);
		shader.doCompile();
		/// check if shader compilation is successfull, fail creation if not
		if(shader.getStatus() != ShaderStatus::COMPILED) {
			throw std::exception();
		}
		glAttachShader(program.mInternalId, shader.mInternalId);
		GLProgram p = GLProgram::create(program, rest...);
		if(program.mStatus == GLProgramStatus::COMPILED) {
			glDetachShader(program.mInternalId, shader.mInternalId);
		}
		return program;
	}

	static GLProgram create(GLProgram& program);

};

}

#endif //GANESHENGINE_GHGLPROGRAM_H
