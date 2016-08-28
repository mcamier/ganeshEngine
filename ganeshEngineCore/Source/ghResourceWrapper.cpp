#include "ghResourceWrapper.h"

namespace ganeshEngine {

void ResourceWrapper::setData(shared_ptr <Resource> data) {
    this->data = data;
}

shared_ptr<Resource> ResourceWrapper::getData() const {
    return this->data;
}

bool ResourceWrapper::isEagerLoadAllowed() const {
    return this->eagerLoading;
}
const string& ResourceWrapper::getName() const {
    return this->name;
}

bool ResourceWrapper::isLoaded() const {
    if (data != nullptr) {
        if (data->needGcLoad() && !data->isGcLoaded()) {
            return false;
        }
        return true;
    }
    return false;
}

void ResourceWrapper::load() {
    if(!isLoaded()) {
        setData(loader->load(filename.c_str()));
        if(data->needGcLoad() && !data->isGcLoaded()) {
            data->sendToGc();
        }
    }
}

}