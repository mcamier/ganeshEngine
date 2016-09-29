#ifndef GANESHENGINE_GHRESOURCE_H
#define GANESHENGINE_GHRESOURCE_H

namespace ganeshEngine {

/**
 * All Object that could be used as resource should inherit this base class
 */
class Resource {
    friend class ResourceWrapper;

private:
    /** Specify whether resource need to be uploaded to GC to be properly used */
    bool m_needGcInit;

public:
    Resource(bool needGcInit) : m_needGcInit(needGcInit) {}

    Resource(const Resource &) = delete;

    Resource &operator=(const Resource &) = delete;

    virtual ~Resource() {}

    /**
     * Indicates if resource need to be loaded on GC's memory
     * @return true if resource need to be loaded, false otherwise
     */
    bool needGcLoad() const { return m_needGcInit; }

protected:
    /**
     * Load the resource into the GC memory
     * @return True if upload to GC happened without trouble, false otherwise
     */
    virtual bool sendToGc() {return true;};

    /**
     * Remove the resource from the GC memory, this object will stay unchanged
     * @return True if memory freeing happened without trouble, false otherwise
     */
    virtual bool freeFromGc() {return true;};
};

}
#endif //GANESHENGINE_GHRESOURCE_H