#include "ghResource.h"

namespace ganeshEngine {

    void ResourceManager::vInitialize() {
        //m_resourcesMap.insert(pair<U32, shared_ptr<IResource>>(1, r));
    }

    void ResourceManager::vDestroy() {
    }

    ResourceManager &(*gResource)() = &ResourceManager::get;
}