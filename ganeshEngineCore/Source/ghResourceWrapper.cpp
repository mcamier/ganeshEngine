#include "ghResourceWrapper.h"

#include "ghResourceManager.h"
#include "ghResourceLoader.h"

namespace ganeshEngine {

void ResourceWrapper::setData(shared_ptr<Resource> data) {
    this->data = data;
}

shared_ptr<Resource> ResourceWrapper::getData() const {
    return this->data;
}

bool ResourceWrapper::isEagerLoadAllowed() const {
    return this->mEagerLoading;
}
const string& ResourceWrapper::getName() const {
    return this->mInfos.getName();
}

bool ResourceWrapper::isLoaded() const {
    /* check for dependencies in memory presence, return false if any of them is missing */
    for(auto dep : mInfos.getDependencies()) {
        if(!gResource().isLoaded(dep.second)) {
            return false;
        }
    }
    /* check if resource is well loaded, as well as loaded in GC memory if needed*/
    if (data != nullptr) {
        if (data->needGcLoad() && !mIsGccLoaded) {
            return false;
        }
        return true;
    }
    return false;
}

bool ResourceWrapper::load() {
    if(!isLoaded()) {

        setData(mLoader->load(mInfos));

        if(getData() == nullptr) {
            return false;
        }

        if(data->needGcLoad() && !mIsGccLoaded) {
            return data->sendToGc();
        }
    }
    return true;
}

}