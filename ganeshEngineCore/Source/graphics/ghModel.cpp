#include "graphics/ghModel.h"

namespace ganeshEngine {

    void Model::sendToGC() {
        glGenVertexArrays(1, &mVAO);
        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mpMesh->mVBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, x));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, r));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, u));
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, nx));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glBindVertexArray(0);
    }

    ResourceHandler<ShaderProgram> Model::getProgram() {
        return mpProgram;
    }

    void Model::preRender() {
        mpProgram->use();
        glBindVertexArray(mVAO);

    }

    void Model::postRender() {
        glBindVertexArray(0);
        mpProgram->stopUsing();
    }

    void Model::render() {
        glDrawArrays((GLenum) mpMesh->mDrawMode, 0, (int) mpMesh->mVertices->size());
    }
}