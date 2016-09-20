#include "render/ghMesh.hpp"

namespace ganeshEngine {

bool Mesh::sendToGc() {
    /*
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return Resource::sendToGc();
     */
    return false;
}

bool Mesh::freeFromGc() {
    return Resource::freeFromGc();
}

}