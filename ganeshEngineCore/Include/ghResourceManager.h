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

    string m_resourceLocation;

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
     * Returns a resourceHandler
     *
     * @param resourceId Id of the resource to get
     * @return resourceHandler on the resource
     */
    template<typename T> ResourceHandler<T> getResource(long resourceId);

    /**
     *
     * @param resourceId
     */
    void loadResource(long resourceId);

protected:
    void vInitialize();
    void vDestroy();
};

extern ResourceManager &(*gResource)();
}

#endif //GANESHENGINE_GHRESOURCEMANAGER_H