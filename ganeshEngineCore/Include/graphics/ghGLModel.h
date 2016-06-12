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

enum class AttribPointer : U32 {
	VERTEX  = 0,
	COLOR   = 1,
	UV      = 2,
	NORMAL  = 3

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
	F32 r, g, b;

	//F32 nx, ny, nz;
	//F32 u, v;

	/*Vertex(F32 _x, F32 _y, F32 _z, F32 _u, F32 _v, F32 _nx, F32 _ny, F32 _nz) :
			x(_x), y(_y), z(_z),
			nx(_nx), ny(ny), nz(_nz),
			u(_u), v(_v) {}*/

	Vertex(F32 _x, F32 _y, F32 _z, F32 _u, F32 _v, F32 _nx, F32 _ny, F32 _nz) :
			x(_x), y(_y), z(_z),
			r(0.3f), g(0.3f), b(1.0f) {}
};


/**
 *
 */
class GLTexture {
public:
	void sendToGC() {}
};


/**
 *
 */
class GLMesh {
	friend class GLModel;

	vector<Vertex> mVertices;
	GLuint mVBO;
	DrawMode mDrawMode;

public:
	GLMesh(vector<Vertex> vertices, DrawMode drawMode) :
		mVertices(vertices),
		mDrawMode(drawMode),
		mVBO(-1) {}
	~GLMesh() {}

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

	void sendToGC() {
		mpMesh->sendToGC();
		mpTexture->sendToGC();

		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mpMesh->mVBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, r));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);

	}

	void draw() {
		glUseProgram(mpProgram->mInternalId);
		glBindVertexArray(mVAO);
		glDrawArrays((GLenum) mpMesh->mDrawMode, 0, (int) mpMesh->mVertices.size());
		glBindVertexArray(0);
	}
};

}

#endif //GANESHENGINE_GHGLMODEL_H
