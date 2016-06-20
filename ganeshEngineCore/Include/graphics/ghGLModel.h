#ifndef GANESHENGINE_GHGLMODEL_H
#define GANESHENGINE_GHGLMODEL_H

#include "graphics/ghHeaders.h"
#include "graphics/ghGLProgram.h"
#include "graphics/ghGLMesh.h"
#include "graphics/ghGLTexture.h"
#include "graphics/ghGLShader.h"

namespace ganeshEngine {

using namespace std;
using namespace glm;


/**
 *
 */
class GLModel {
private:
	/**
	 * The shader program used to draw the geometry
	 */
	GLProgram *mpProgram;

	/**
	 * The mesh to draw
	 */
	GLMesh *mpMesh;

	/**
	 * Optional texture to apply on the mesh
	 */
	GLTexture *mpTexture;

	/**
	 * The id of Vertex Array Object
	 */
	GLuint mVAO;

public:
	GLModel(GLProgram *program, GLMesh *mesh, GLTexture *texture) :
		mpProgram(program), mpMesh(mesh), mpTexture(texture) {}
	~GLModel() {}

	/**
	 * Load the model into the GC memory to use it during the drawing
	 */
	void sendToGC();

	GLProgram* getProgram();

	void preRender();

	void render();

	void postRender();

};

}

#endif //GANESHENGINE_GHGLMODEL_H
