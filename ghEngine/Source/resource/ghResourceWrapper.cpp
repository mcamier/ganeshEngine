#include "resource/ghResourceWrapper.hpp"

#include "resource/ghResourceManager.hpp"

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

const stringId ResourceWrapper::getId() const {
    return this->mId;
}

bool ResourceWrapper::isLoaded() const {
    /* check for dependencies in memory presence, return false if any of them is missing */
    for(auto dep : mInfos.getDependencies()) {
        if(!gResource().isLoaded(dep.second)) {
            return false;
        }
    }
    return data != nullptr;
}

bool ResourceWrapper::load() {
    if(!isLoaded()) {
        setData(mLoader->load(mInfos));
        return getData() != nullptr;
    }
    return true;
}

}