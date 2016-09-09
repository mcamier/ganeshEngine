#ifndef GANESHENGINE_GHRESOURCEIMPORTER_H
#define GANESHENGINE_GHRESOURCEIMPORTER_H

#include <memory>

#include "ghResource.h"
#include "ghResourceUtil.h"

namespace ganeshEngine {

using namespace std;

class ResourceLoader {
public:
    /**
     * Load a file as a generic Resource object and return it via an
     * unique_ptr
     *
     * @param filename path to the file to load
     * @param metadatas
     * @return Unique pointer pointing to loaded resource
     */
    virtual unique_ptr<Resource> load(const ResourceInfos &infos) const = 0;
};

}

#endif //GANESHENGINE_GHRESOURCEIMPORTER_H
