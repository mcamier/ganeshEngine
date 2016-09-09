#include "ghResourceWrapper.h"

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