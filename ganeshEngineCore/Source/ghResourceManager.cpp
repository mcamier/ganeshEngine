#include "ghResourceManager.h"

#include "ghCore.h"

namespace ganeshEngine {

void ResourceManager::vInitialize() {
    // TODO add default loaders here
    if (m_configuration != nullptr) {
        m_resourceLocation = m_configuration->getResourceLocation();
        for (const auto &entry : m_configuration->getResourceEntries()) {

            auto loadersItr = m_loaders.find(gInternString(entry.loaderName.c_str()));
            if (loadersItr != m_loaders.end()) {
                auto ptr = make_shared<ResourceWrapper>(entry.name, entry.filename, loadersItr->second, entry.eagerLoading);

                if(ptr->isEagerLoadAllowed()) {
                    _DEBUG("eager loading for resource : "<<ptr->getName(), LOG_CHANNEL::RESOURCE);
                    if(!ptr->load()) {
                        _ERROR("Something went wrong while loading resource : " << ptr->getName(), LOG_CHANNEL::RESOURCE)
                    }
                }

                m_resources.insert(make_pair(gInternString(entry.name.c_str()), ptr));
            } else {
                _ERROR("Resource doesn't have valid loader present", LOG_CHANNEL::RESOURCE);
            }
        }

        m_configuration.release();
    }
}

void ResourceManager::vDestroy() {}

void ResourceManager::loadResource(stringId resourceId) {
    auto itr = m_resources.find(resourceId);
    if (itr == m_resources.end()) {
        exit(-1);
    }
    shared_ptr<ResourceWrapper> wrapper = itr->second;
    if(!wrapper->load()) {
        _ERROR("Something went wrong while loading resource : " << gStringFromStringId(resourceId), LOG_CHANNEL::RESOURCE)
    }
}

ResourceManager &(*gResource)() = &ResourceManager::get;
}