#ifndef GANESHENGINE_GHRESOURCEWRAOOER_H
#define GANESHENGINE_GHRESOURCEWRAOOER_H

#include <memory>
#include <string>

#include "ghResource.h"
#include "ghResourceLoader.h"
#include "ghResourceUtil.h"

namespace ganeshEngine {

using namespace std;

/**
 * Wrap a Resource
 * This wrapper provides informations about an underlying Resource like its
 * id, name, path and importer instance.
 * ResourceWrapper are manipulated by ResourceManager but are invisible outside
 * of the engine's core
 */
class ResourceWrapper {
private:
    /* the resource */
    shared_ptr<Resource> data;

    /** Unique ID for each resource managed via a ResourceWrapper */
    stringId mId;

    /** Contains all informations about the resources, like name, filename, metadatas or dependencies */
    ResourceInfos mInfos;

    /** Pointer to the loaded to use in order to loaded the underlying resource */
    shared_ptr<ResourceLoader> mLoader;

    /** Load the resource as soon as possible if true, otherwise the resource will be loaded during call to get method */
    bool mEagerLoading;

    /** Store whether the resource is already loaded into the GC memory */
    bool mIsGccLoaded;

public:
    ResourceWrapper(ResourceInfos infos, shared_ptr<ResourceLoader> loader, bool eagerLoading) :
            mInfos(infos),
            mIsGccLoaded(false),
            mEagerLoading(eagerLoading),
            mLoader(loader),
            mId(gInternString(infos.getName().c_str())) {}

    ResourceWrapper(const ResourceWrapper& rw) :
            mInfos(rw.mInfos),
            mIsGccLoaded(rw.mIsGccLoaded),
            mEagerLoading(rw.mEagerLoading),
            mLoader(rw.mLoader),
            mId(gInternString(rw.mInfos.getName().c_str())) {}

    ResourceWrapper &operator=(const ResourceWrapper& rw) = default;

    ~ResourceWrapper() {}

    /**
     * Set the Resource pointed by the wrapper
     * @param Resource pointed by the wrapper
     */
    void setData(shared_ptr<Resource> data);

    /**
     * Provides shared_ptr to the underlying Resource
     * @return pointer to the Resource
     */
    shared_ptr<Resource> getData() const;

    /**
     * Indicates whether the underlying Resource is loaded
     * @return true if loaded, false otherwise
     */
    bool isLoaded() const;

    /**
     * Indicates whether the underlying Resource can be loaded ASAP by the resource
     * manager
     * @return true if eager load allowed, false otherwise
     */
    bool isEagerLoadAllowed() const;

    /**
     * Getter of the resource's name
     * @return name of the resource
     */
    const string& getName() const;

    /**
     * Load the underlying resource with the embedded resourceLoader
     */
    bool load();
};

}
#endif //GANESHENGINE_GHRESOURCEWRAOOER_H
