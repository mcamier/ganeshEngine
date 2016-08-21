#include "ghHeaders.h"
#include "ghSystem.h"
#include "ghResourceConfiguration.h"
#include "ghResourceImporter.h"

namespace ganeshEngine {

using namespace std;


/**
 * Base class for resource's handler for polymorphism purpose
 */
class IResourceHandler {
public:
    virtual ~IResourceHandler() {}
};


/**
 * Resource hold in memory a unique pointer on the resource data
 */
template<typename T>
class ResourceHandler : public IResourceHandler {
private:
    T* m_object;

public:
    ResourceHandler(T* object) : m_object(object) {}

    virtual ~ResourceHandler() {
        free(m_object);
    }

    /**
     * @note The result pointer must not be stored to be reused later
     *
     * @return pointer to resource raw data
     */
    const T* const getRaw() const {
        return m_object;
    }
};


using hIResource = shared_ptr<IResourceHandler>;

template<typename T>
using hResource = shared_ptr<ResourceHandler<T>>;


/**
 *
 */
class Resource {
friend class ResourceManager;

protected:
    U32 m_id;
    string m_name;
    string m_filename;
    string m_importerName;
    U32 m_importerHashId;

private:
    hIResource m_resourceHandler;

public:
    Resource(const string& name, const string& filename, const string& importerName) :
            m_id(GH_HASH(name)),
            m_name(name),
            m_filename(filename),
            m_importerName(importerName),
            m_importerHashId(GH_HASH(importerName)) {}

    Resource(const Resource &) = delete;
    Resource &operator=(const Resource &) = delete;

    const U32 getId() const { return m_id; }
    const string& getName() const { return m_name; }
    const string& getFilename() const { return m_filename; }
    const string& getImporterName() const { return m_importerName; }
    const U32 getImporterHashId() const { return m_importerHashId; }
    const hIResource getResourceHandler() const { return m_resourceHandler; }

    bool isLoaded() const { return (m_resourceHandler!=nullptr); }
};


/**
 *
 */
class ResourceManager : public System<ResourceManager> {
    friend class System<ResourceManager>;

private:
    /**
     * Configuration object, holding all informations used to initialization
     * the manager
     */
    unique_ptr<ResourceConfiguration> m_configuration;
    ResourceLocationType m_resourceLocationType;
    string m_resourceLocation;

    map<U32, unique_ptr<Resource>> m_resources;
    map<U32, IResourceLoader*> m_importers;

    ResourceManager(unique_ptr<ResourceConfiguration> conf) : m_configuration(move(conf)) {}

public:
    ResourceManager(const ResourceManager &) = delete;

    ResourceManager &operator=(const ResourceManager &) = delete;

    virtual ~ResourceManager() {}

    template<typename T>
    hResource<T> getResource(U32 resourceId) {
        auto itr = m_resources.find(resourceId);
        if(itr==m_resources.end()) {
            return nullptr;
        }
        const auto& res = itr->second;
        if(!res->isLoaded()) {
            //load resource
            load<T>(resourceId);
            _DEBUG("Resource missing in memory, load it", LOG_CHANNEL::DEFAULT);
        }
        return dynamic_pointer_cast<ResourceHandler<T>>(res->getResourceHandler());
    }

    void addImporter(string importerName, IResourceLoader* loader) {
        m_importers.insert(make_pair(GH_HASH(importerName), loader));
    }

    template<typename T>
    void load(U32 resourceId) {
        auto itrRes = m_resources.find(resourceId);
        if(itrRes == m_resources.end()) {
            _WARNING("Unable to load the resource with id : " << resourceId, LOG_CHANNEL::DEFAULT);
            return;
        }
        auto& res = itrRes->second;

        auto itrImporter = m_importers.find(res->getImporterHashId());
        if(itrImporter == m_importers.end()) {
            _WARNING("Unable to find importer with id : " << resourceId, LOG_CHANNEL::DEFAULT);
            return;
        }
        T* data = reinterpret_cast<T*>((itrImporter->second)->load(res->getFilename()));
        res->m_resourceHandler = make_shared<ResourceHandler<T>>(data);
    }

protected:
    void vInitialize();

    void vDestroy();
};

extern ResourceManager &(*gResource)();
}