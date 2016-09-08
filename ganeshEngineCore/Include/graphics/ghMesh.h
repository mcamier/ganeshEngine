#ifndef GANESHENGINE_GHGLMESH_H
#define GANESHENGINE_GHGLMESH_H

#include "../ghHeaders.h"
#include "graphics/ghHeaders.h"

#include "ghResource.h"

namespace ganeshEngine {

using namespace std;

class Mesh : public Resource {
    friend class Model;

private:
    unique_ptr<vector<Vertex>> mVertices{nullptr};
    DrawMode mDrawMode;
    GLuint mVBO;

public:
    Mesh() {}

    Mesh(unique_ptr<vector<Vertex>> vertices, DrawMode drawMode) :
            mVertices(std::move(vertices)), mDrawMode(drawMode), mVBO(-1) {}

    ~Mesh() {}

    bool sendToGc();

    bool freeFromGc();
};

}

#endif //GANESHENGINE_GHGLMESH_H
