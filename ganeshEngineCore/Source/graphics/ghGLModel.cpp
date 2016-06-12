#include "graphics/ghGLModel.h"

namespace ganeshEngine {

void GLTexture::sendToGC() {}

void GLMesh::sendToGC() {
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(
			GL_ARRAY_BUFFER,
			mVertices->size() * sizeof(Vertex),
			&mVertices->front(),
			GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

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

void GLModel::draw() {
	glUseProgram(mpProgram->mInternalId);
	glBindVertexArray(mVAO);
	glDrawArrays((GLenum) mpMesh->mDrawMode, 0, (int) mpMesh->mVertices->size());
	glBindVertexArray(0);
}
}