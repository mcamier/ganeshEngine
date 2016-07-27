#ifndef GANESHENGINE_GHGLMESH_H
#define GANESHENGINE_GHGLMESH_H

#include "../ghHeaders.h"
#include "graphics/ghHeaders.h"

namespace ganeshEngine {

    using namespace std;

/**
 *
 */
    class GLMesh {
        friend class GLModel;

        unique_ptr<vector<Vertex>> mVertices{nullptr};
        DrawMode mDrawMode;
        GLuint mVBO;

    public:
        GLMesh(unique_ptr<vector<Vertex>> vertices, DrawMode drawMode) :
                mVertices(std::move(vertices)), mDrawMode(drawMode), mVBO(-1) {}

        ~GLMesh() {}

        void sendToGC();
    };

}

#endif //GANESHENGINE_GHGLMESH_H
