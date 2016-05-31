#include "graphics/ghGLProgram.h"

namespace ganeshEngine {

GLProgram GLProgram::create(GLProgram& program) {
	glLinkProgram(program.mInternalId);

	/// error checking
	int isLinked = 0;
	glGetProgramiv(program.mInternalId, GL_LINK_STATUS, &isLinked);
	if(isLinked == GL_TRUE) {
		program.mStatus = GLProgramStatus::COMPILED;
	} else if(isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(program.mInternalId, GL_INFO_LOG_LENGTH, &maxLength);
		char *strInfoLog = new char[maxLength + 1];
		glGetProgramInfoLog(program.mInternalId, maxLength, nullptr, strInfoLog);
		strInfoLog[maxLength] = '\0';
		glDeleteProgram(program.mInternalId);
		std::cerr << strInfoLog << std::endl;
		delete[] strInfoLog;
		program.mStatus = GLProgramStatus::FAILED;
	}
	return program;
}

}