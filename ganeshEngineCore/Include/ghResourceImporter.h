#ifndef GANESHENGINE_GHRESOURCEIMPORTER_H
#define GANESHENGINE_GHRESOURCEIMPORTER_H

#include "ghHeaders.h"
#include <fstream>

namespace ganeshEngine {

using namespace std;

class MeshObj {

};

/**
 *
 */
class IResourceLoader {
public:
    virtual void* load(string filename) = 0;
};


/**
 *
 */
template<typename T>
class ResourceLoader : public IResourceLoader {
protected:
    void* load(string filename) {
        void* base = static_cast<void*>(specificLoad(filename));
        if(base == nullptr) {
            _WARNING("fail to importer resource : " << filename, LOG_CHANNEL::DEFAULT);
        }
        return base;
    }

    virtual T* specificLoad(string filename) = 0;
};

class mesh_v{
public:
	float x, y, z, w;
};
class mesh_vt{
public:
	float u, v, w;
};
class mesh_vn{
public:
	float i, j, k;
};

class ObjResourceLoader : public ResourceLoader<MeshObj> {
protected:
    virtual MeshObj* specificLoad(string filename) {
		vector<mesh_v> list_v;
		vector<mesh_vt> list_vt;
		vector<mesh_vn> list_vn;
		char test[100];

        std::ifstream infile(filename);
        std::string line;

        while (std::getline(infile, line))
        {
			std::istringstream iline(line);
			std::string type;
			iline >> type;

			if(type.compare("v") == 0) {
				mesh_v _v;
				iline >> _v.x >> _v.y >> _v.z;
				if(!iline.eof()){
					iline >> _v.w;
				} else {
					_v.w = 1.0f;
				}
				_DEBUG("v", LOG_CHANNEL::DEFAULT);
			}
        }
		_DEBUG("NOK", LOG_CHANNEL::DEFAULT);
    }
};

}

#endif //GANESHENGINE_GHRESOURCEIMPORTER_H
