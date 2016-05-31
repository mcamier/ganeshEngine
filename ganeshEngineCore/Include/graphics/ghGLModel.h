#ifndef GANESHENGINE_GHGLMODEL_H
#define GANESHENGINE_GHGLMODEL_H

#include "../ghHeaders.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/ghGLProgram.h"
#include "graphics/ghGLShader.h"

namespace ganeshEngine {

using namespace std;

class GLTexture {

};

class GLMaterial {
private:
	GLTexture *mpGlTexture;
	vector<vector3f> mUVCoords;
};

class GLModel {
private:
	GLProgram* mpGlProgram;
	GLMaterial* mpGlMaterial;

	array<GLfloat> mVertices;

	GLuint mVao;
	GLuint mVbo;
	GLenum mDrawMode;
	U32 mVerticesCount;

	GLModel() {}
	~GLModel() {}

public:
	static GLModel* make() {
		GLModel *model = new GLModel();
		model->mDrawMode = GL_TRIANGLES;
		model->mVertices.insert(0.0f);
		model->mVertices.insert(0.8f);
		model->mVertices.insert(0.0f);
		model->mVertices.insert(-0.8f);
		model->mVertices.insert(-0.8f);
		model->mVertices.insert(0.0f);
		model->mVertices.insert(0.8f);
		model->mVertices.insert(-0.8f);
		model->mVertices.insert(0.0f);

		glGenVertexArrays(1, &(model->mVao));
		glBindVertexArray(model->mVao);

		glGenBuffers(1, &(model->mVbo));
		glBindBuffer(GL_ARRAY_BUFFER, model->mVbo);

		glBufferData(GL_ARRAY_BUFFER, model->mVertices.size(), model->mVertices, GL_STATIC_DRAW);
		GLint vert = glGetAttribLocation(mpGlProgram->mInternalId, "vert");
		glEnableVertexAttribArray(vert, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return model;
	}

};

}

#endif //GANESHENGINE_GHGLMODEL_H
