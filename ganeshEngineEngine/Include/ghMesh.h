#ifndef GANESHENGINE_GHGLMESH_H
#define GANESHENGINE_GHGLMESH_H

#include "ghHeaders.h"
#include "ghGheaders.h"

#include "ghResource.h"

#include <vector>
#include <glm/glm.hpp>

namespace ganeshEngine {

using namespace glm;
using namespace std;

class Mesh : public Resource {
friend class Model;
friend class ObjModelLoader;

private:
    vector<Vertex> mVertices;
    DrawMode mDrawMode;
    GLuint mVBO;

public:
    Mesh() : Resource(true), mDrawMode(DrawMode::TRIANGLES), mVBO(-1) {}
    ~Mesh() {}

protected:
    bool sendToGc() override;
    bool freeFromGc() override;
};

}

#endif //GANESHENGINE_GHGLMESH_H
