#ifndef GANESHENGINE_GHGLMODEL_H
#define GANESHENGINE_GHGLMODEL_H

#include "../ghHeaders.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "graphics/ghGLProgram.h"
#include "graphics/ghGLShader.h"

namespace ganeshEngine {

using namespace std;
using namespace glm;

class GLTexture {

};

class GLMaterial {
private:
	GLTexture *mpGlTexture;
	vector<vec3> mUVCoords;
};

class GLModel {
private:
	GLProgram mpGlProgram;
	GLMaterial mpGlMaterial;

	GLfloat* mVertices;

	GLuint mVao;
	GLuint mVbo;
	GLenum mDrawMode;
	U32 mVerticesCount;

	GLModel() {}
	~GLModel() {}

public:
	static GLModel* make() {
		GLModel *model = new GLModel();
		model->mpGlProgram = GLProgram::create(ShaderType::VERTEX, "/home/mcamier/Workspace/ganeshEngine/ganeshEngineDemo/Resources/vDefault.glsl", ShaderType::FRAGMENT, "/home/mcamier/Workspace/ganeshEngine/ganeshEngineDemo/Resources/fDefault.glsl");

		model->mDrawMode = GL_TRIANGLES;
		model->mVerticesCount = 9;
		model->mVertices = (GLfloat*)malloc(sizeof(GLfloat) * model->mVerticesCount);
		model->mVertices[0] = 0.0f;
		model->mVertices[1] = 0.8f;
		model->mVertices[2] = 0.0f;
		model->mVertices[3] = -0.8f;
		model->mVertices[4] = -0.8f;
		model->mVertices[5] = 0.0f;
		model->mVertices[6] = 0.8f;
		model->mVertices[7] = -0.8f;
		model->mVertices[8] = 0.0f;

		glGenVertexArrays(1, &(model->mVao));
		glBindVertexArray(model->mVao);

		glGenBuffers(1, &(model->mVbo));
		glBindBuffer(GL_ARRAY_BUFFER, model->mVbo);

		glBufferData(GL_ARRAY_BUFFER, model->mVerticesCount, model->mVertices, GL_STATIC_DRAW);
		GLint vert = glGetAttribLocation(model->mpGlProgram.mInternalId, "vert");
		glEnableVertexAttribArray(vert);
		glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return model;
	}

	const GLint getGlProgramId() const {
		return mpGlProgram.mInternalId;
	}

	const GLuint getVao() const {
		return mVao;
	}

	const GLuint getVbo() const {
		return mVbo;
	}

	const GLuint getDrawMode() const {
		return mDrawMode;
	}



};

}

#endif //GANESHENGINE_GHGLMODEL_H
