#ifndef GANESHENGINE_GHGLMESH_H
#define GANESHENGINE_GHGLMESH_H


#include "ghGheaders.hpp"

#include "resource/ghResource.hpp"

#include <vector>
#include <glm/glm.hpp>

namespace ganeshEngine {

using namespace glm;
using namespace std;

class Mesh : public Resource {
friend class Model;
friend class ObjModelLoader;

private:
    vector<float> mBuffer;
    DrawMode mDrawMode;

public:
    Mesh() :
            Resource(),
            mBuffer(vector<float>()),
            mDrawMode(DrawMode::TRIANGLES) {}
    ~Mesh() {}

    vector<float>* getBuffer() {
        return &mBuffer;
    }

};

}

#endif //GANESHENGINE_GHGLMESH_H
