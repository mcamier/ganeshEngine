#include "ghResource.h"

namespace ganeshEngine {
    void ResourceManager::vInitialize() {
        auto d = make_unique<Dummy>(666, 0.5f);
        auto r = make_shared<Resource<Dummy>>(move(d));
        m_resourcesMap.insert(pair<U32, shared_ptr<IResource>>(1, r));
    }


    void ResourceManager::vDestroy()
    {
    }

ResourceManager&(*gResource)() = &ResourceManager::get;
}