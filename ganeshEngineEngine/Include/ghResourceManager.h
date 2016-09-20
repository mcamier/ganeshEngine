#ifndef GANESHENGINE_GHRESOURCEMANAGER_H
#define GANESHENGINE_GHRESOURCEMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"
#include "ghResourceLoader.h"
#include "ghResourceWrapper.h"
#include "ghResourceHandler.h"
#include "ghResourceConfiguration.h"

#include <type_traits>

namespace ganeshEngine {

using namespace std;

/**
 *
 */
class ResourceManager : public System<ResourceManager> {
    friend class System<ResourceManager>;
    friend class Application;

private:
    /** Configuration object, holding all informations used to initialization
     * the manager */
    unique_ptr<ResourceConfiguration> m_configuration;

    /** Registered resources loaders */
    map<stringId, shared_ptr<ResourceLoader>> m_loaders;

    /** Resource registry */
    map<stringId, shared_ptr<ResourceWrapper>> m_resources;

    ResourceManager(unique_ptr<ResourceConfiguration> conf, map<U32, ResourceLoader*> loaders) :
            m_configuration(move(conf)) {
        /** Register customs resource's loaders */
        for(auto itr = loaders.begin() ; itr != loaders.end(); ++itr) {
            m_loaders.insert(make_pair(itr->first, shared_ptr<ResourceLoader>(itr->second)));
        }
    }

public:
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;
    virtual ~ResourceManager() {}

    /**
     * Returns a resourceHandler to the requested resource of the given type T
     *
     * @param resourceId Id of the resource to get
     * @return resourceHandler on the resource
     */
    template<typename T> ResourceHandler<T> getResource(stringId resourceId) {
        ASSERT((is_base_of<Resource, T>::value));

        auto itr = m_resources.find(resourceId);
        if (itr == m_resources.end()) {
            exit(-1);
        }

        itr->second->load();

        return ResourceHandler<T>(itr->second);
    }

    /**
     * Returns a resourceHandler to the requested resource of the generic type Resource
     *
     * @param resourceId
     * @return
     */
    ResourceHandler<Resource> getResource(stringId resourceId) {
        auto itr = m_resources.find(resourceId);
        if (itr == m_resources.end()) {
            exit(-1);
        }
        //itr->second->load();
        return ResourceHandler<Resource>(itr->second);
    }

    /**
     *
     * @param resourceId
     */
    void loadResource(stringId resourceId);

    bool isLoaded(stringId resourceId);

protected:
    void vInitialize();
    void vDestroy();

    void doEagerLoading();
};

extern ResourceManager &(*gResource)();
}

#endif //GANESHENGINE_GHRESOURCEMANAGER_H