#include "ghResource.h"

namespace ganeshEngine {


void ResourceManager::vInitialize() {
    if (m_configuration != nullptr) {
        this->m_resourceLocationType = m_configuration->getResourceLocationType();
        this->m_resourceLocation = m_configuration->getResourceLocation();
        for(resourceEntry& re : m_configuration->getResourceEntries()) {
            m_resources.insert(make_pair(
                    GH_HASH(re.name),
                    make_unique<Resource>(re.name, re.filename, re.importerName)
            ));
        }
        m_configuration.release();
    }
}

void ResourceManager::vDestroy() {}

ResourceManager &(*gResource)() = &ResourceManager::get;
}