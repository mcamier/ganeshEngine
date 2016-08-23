#include "ghResourceManager.h"

namespace ganeshEngine {


void ResourceManager::vInitialize() {
    // TODO add default loaders here

    if (m_configuration != nullptr) {
        m_resourceLocation = m_configuration->getResourceLocation();
        for (const auto &entry : m_configuration->getResourceEntries()) {

            auto loadersItr = m_loaders.find(GH_HASH(entry.loaderName));
            if (loadersItr != m_loaders.end()) {
                auto ptr = make_shared<ResourceWrapper>(entry.name, entry.filename, loadersItr->second, entry.eagerLoading);
                m_resources.insert(make_pair(GH_HASH(entry.name), ptr));
            } else {
                _ERROR("Resource doesn't have valid loader present", LOG_CHANNEL::RESOURCE);
            }
        }

        m_configuration.release();
    }
}

void ResourceManager::vDestroy() {}

template<typename T>
ResourceHandler<T> ResourceManager::getResource(long resourceId) {
    auto itr = m_resources.find(resourceId);
    if (itr == m_resources.end()) {
        exit(-1);
    }
    return ResourceHandler<T>(itr->second);
}

void ResourceManager::loadResource(long resourceId) {
    auto itr = m_resources.find(resourceId);
    if (itr == m_resources.end()) {
        exit(-1);
    }
    shared_ptr<ResourceWrapper> wrapper = itr->second;
    wrapper->load();
}

ResourceManager &(*gResource)() = &ResourceManager::get;
}