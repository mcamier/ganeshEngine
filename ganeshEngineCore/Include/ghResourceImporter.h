#ifndef GANESHENGINE_GHRESOURCEIMPORTER_H
#define GANESHENGINE_GHRESOURCEIMPORTER_H

#include "ghHeaders.h"
#include "graphics/ghHeaders.h"
#include "graphics/ghGLShader.h"
#include "graphics/ghGLProgram.h"
#include <fstream>

namespace ganeshEngine {

using namespace std;

class Resource;

/**
 *
 */
class IResourceLoader {
public:
    virtual void *load(Resource& resource) = 0;
};


/**
 *
 */
template<typename T>
class ResourceLoader : public IResourceLoader {
protected:
    void *load(Resource& resource);

    virtual T *specificLoad(Resource& resource) = 0;
};

class mesh_v {
public:
    float x, y, z, w;
};

class mesh_vt {
public:
    float u, v, w;
};

class mesh_vn {
public:
    float i, j, k;
};


class GLShaderResourceLoader : public ResourceLoader<GLShader> {
protected:
    virtual GLShader *specificLoad(Resource& resource);
};


class GLProgramResourceLoader : public ResourceLoader<GLProgram> {
protected:
    virtual GLProgram *specificLoad(Resource& resource);
};


/*class ObjResourceLoader : public ResourceLoader<MeshObj> {
protected:
    virtual MeshObj *specificLoad(Resource& resource) {
        vector<mesh_v> list_v;
        vector<mesh_vt> list_vt;
        vector<mesh_vn> list_vn;
        char test[100];

        std::ifstream infile("    TO REPLACE ");
        std::string line;

        while (std::getline(infile, line)) {
            std::istringstream iline(line);
            std::string type;
            iline >> type;

            if (type.compare("v") == 0) {
                mesh_v _v;
                iline >> _v.x >> _v.y >> _v.z;
                if (!iline.eof()) {
                    iline >> _v.w;
                } else {
                    _v.w = 1.0f;
                }
                _DEBUG("v", LOG_CHANNEL::DEFAULT);
            }
        }
        _DEBUG("NOK", LOG_CHANNEL::DEFAULT);
    }
};*/

}

#endif //GANESHENGINE_GHRESOURCEIMPORTER_H
