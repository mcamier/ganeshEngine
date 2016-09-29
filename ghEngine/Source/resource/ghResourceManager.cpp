#include "resource/ghResourceManager.hpp"

#include "resource/ghResourceLoaders.hpp"

namespace ganeshEngine {

void ResourceManager::vInitialize() {
    m_loaders.insert(make_pair(ghTextureLoaderName, make_shared<PngTextureLoader>()));
    m_loaders.insert(make_pair(ghObjLoaderName, make_shared<ObjModelLoader>()));
    m_loaders.insert(make_pair(ghShaderLoaderName, make_shared<ShaderLoader>()));
    m_loaders.insert(make_pair(ghShaderProgramLoaderName, make_shared<ShaderProgramLoader>()));
}

void ResourceManager::loadConfiguration(ResourceConfiguration* configuration) {
    if (configuration != nullptr) {
        for (auto &entry : configuration->getResourceEntries()) {

            auto loadersItr = m_loaders.find(gInternString(entry.loaderName.c_str()));
            if (loadersItr != m_loaders.end()) {
                ResourceInfos infos = ResourceInfos(entry.name, entry.filename, entry.metadatas, entry.dependencies);

                auto ptr = make_shared<ResourceWrapper>(infos, loadersItr->second, entry.eagerLoading);
                m_resources.insert(make_pair(gInternString(entry.name.c_str()), ptr));
            } else {
                _ERROR("Resource doesn't have valid loader present", LOG_CHANNEL::RESOURCE);
            }
        }
    }
}

void ResourceManager::doEagerLoading() {
    for(auto& res : m_resources) {
        if(res.second->isEagerLoadAllowed()) {
            _DEBUG("eager loading for resource : " << res.second->getName(), LOG_CHANNEL::RESOURCE);
            if(!res.second->load()) {
                _ERROR("Something went wrong while loading resource : " << res.second->getName(), LOG_CHANNEL::RESOURCE)
            }
        }
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

bool ResourceManager::isLoaded(stringId resourceId) {
    auto itr = m_resources.find(resourceId);
    if (itr == m_resources.end()) {
        return false;
    }
    return itr->second->isLoaded();
}

ResourceManager &(*gResource)() = &ResourceManager::get;
}