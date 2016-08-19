#include "ghResource.h"

namespace ganeshEngine {

    void ResourceManager::vInitialize() {
        if(m_configuration) {
            this->m_resourceLocationType = m_configuration->getResourceLocationType();
            this->m_resourceLocation = m_configuration->getResourceLocation();

            m_configuration.release();
        }
    }

    void ResourceManager::vDestroy() {
    }

    ResourceManager &(*gResource)() = &ResourceManager::get;
}