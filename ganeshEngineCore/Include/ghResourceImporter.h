#ifndef GANESHENGINE_GHRESOURCEIMPORTER_H
#define GANESHENGINE_GHRESOURCEIMPORTER_H

#include "ghHeaders.h"

namespace ganeshEngine {

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

}

#endif //GANESHENGINE_GHRESOURCEIMPORTER_H
