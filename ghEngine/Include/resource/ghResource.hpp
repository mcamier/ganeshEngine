#ifndef GANESHENGINE_GHRESOURCE_H
#define GANESHENGINE_GHRESOURCE_H

namespace ganeshEngine {

/**
 * All Object that could be used as resource should inherit this base class
 */
class Resource {
    friend class ResourceWrapper;

public:
    Resource() {}

    Resource(const Resource &) = delete;

    Resource &operator=(const Resource &) = delete;

    virtual ~Resource() {}

};

}
#endif //GANESHENGINE_GHRESOURCE_H