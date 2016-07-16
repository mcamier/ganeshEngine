#include "graphics/ghGLModel.h"

#include <GL/gl.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ganeshEngine {

    void GLModel::sendToGC() {
	mpMesh->sendToGC();
	mpTexture->sendToGC();

    glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mpMesh->mVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, r));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, nx));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glBindVertexArray(0);

}

GLProgram* GLModel::getProgram() {
	return mpProgram;
}

void GLModel::preRender() {
	mpProgram->use();
	glBindVertexArray(mVAO);

}

void GLModel::postRender() {
	glBindVertexArray(0);
	mpProgram->stopUsing();
}

void GLModel::render() {
	glDrawArrays((GLenum) mpMesh->mDrawMode, 0, (int) mpMesh->mVertices->size());
}
}