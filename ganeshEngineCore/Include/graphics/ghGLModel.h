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
	GLProgram *mpProgram;
	GLMesh *mpMesh;
	GLTexture *mpTexture;

	GLuint mVAO;

public:
	GLModel(GLProgram *program, GLMesh *mesh, GLTexture *texture) :
		mpProgram(program), mpMesh(mesh), mpTexture(texture) {}
	~GLModel() {}

	void sendToGC();

	void draw();
};

}

#endif //GANESHENGINE_GHGLMODEL_H
