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


enum class DrawMode : GLenum {
	POINTS          = GL_POINTS,
	LINES           = GL_LINES,
	LINE_STRIP      = GL_LINE_STRIP,
	LINE_LOOP       = GL_LINE_LOOP,
	TRIANGLES       = GL_TRIANGLES,
	TRIANGLE_STRIP  = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN    = GL_TRIANGLE_FAN
};


enum class VertexInfo : U32 {
	X  = 1,
	Y  = 2,
	Z  = 4,
	W  = 8,
	U  = 16,
	V  = 32,
	NX = 64,
	NY = 128,
	NZ = 256
};


/**
 * Store each informations needed by a given vertex : its location in space
 * texture position, the normal and a color
 */
class Vertex {

public:
	F32 x, y, z;
	//F32 nx, ny, nz;
	//F32 u, v;

	/*Vertex(F32 _x, F32 _y, F32 _z, F32 _u, F32 _v, F32 _nx, F32 _ny, F32 _nz) :
			x(_x), y(_y), z(_z),
			nx(_nx), ny(ny), nz(_nz),
			u(_u), v(_v) {}*/

	Vertex(F32 _x, F32 _y, F32 _z, F32 _u, F32 _v, F32 _nx, F32 _ny, F32 _nz) :
			x(_x), y(_y), z(_z) {}
};


/**
 *
 */
class GLTexture {
public:
	/**
	 * @return
	 */
	bool isLoaded() const {
		return true;
	}

	void sendToGC() {}
};


/**
 *
 */
class GLMesh {
	vector<Vertex> mVertices;
	GLuint mVBO;
	DrawMode mDrawMode;

public:
	GLMesh(vector<Vertex> vertices, DrawMode drawMode) : mVertices(vertices), mDrawMode(drawMode) {}
	~GLMesh() {}

	/**
	 * @return
	 */
	bool isLoaded() const {
		return mVBO >= 0;
	}

	void sendToGC() {
		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(
			GL_ARRAY_BUFFER,
			mVertices.size() * sizeof(Vertex),
			&mVertices.front(),
			GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

};


/**
 *
 */
class GLModel {
private:
	GLProgram *mpProgram;
	GLMesh *mpMesh;
	GLTexture *mpTexture;

	GLuint mVAO;

public:
	GLModel(GLProgram *program, GLMesh *mesh, GLTexture *texture) :
		mpProgram(program),
		mpMesh(mesh),
		mpTexture(texture) {}
	~GLModel() {}

	/**
	 *
	 * @return
	 */
	bool isLoaded() const {
		return true;
	}

	void sendToGC() {
		if (!mpMesh->isLoaded()) mpMesh->sendToGC();
		if (!mpTexture->isLoaded()) mpTexture->sendToGC();

		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
		GLint vert = glGetAttribLocation(mpProgram->mInternalId, "vert");
		glEnableVertexAttribArray(vert);
		glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glBindVertexArray(0);

	}

	void draw() {
		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
};

}

#endif //GANESHENGINE_GHGLMODEL_H
