#ifndef GANESHENGINE_GHRESOURCE_H
#define GANESHENGINE_GHRESOURCE_H

#include "ghHeaders.h"

namespace ganeshEngine {

/**
 * All Object that could be used as resource should
 * inherit this base class
 */
class Resource {
private:
    /** Specify whether resource need to be uploaded to GC to be properly used */
    bool m_needGcInit;

    /** Specify whether resource is already uploaded in GC memory */
    bool m_isGcLoaded;

public:
    Resource() : m_needGcInit(false), m_isGcLoaded(false) {}

    Resource(bool needGcInit) : m_needGcInit(needGcInit), m_isGcLoaded(false) {}

    Resource(const Resource &) = delete;

    Resource &operator=(const Resource &) = delete;

    virtual ~Resource() {}

    /**
     * Load the resource to GC memory
     * @return True is upload to GC happened without trouble, false otherwise
     */
    virtual bool sendToGc() { return true; };

    /**
     * Remove the resource from the GC memory, this object still unchanged
     * @return True is memory freeing happened without trouble, false otherwise
     */
    virtual bool freeFromGc() { return true; };

    /**
     * Indicates if resource is loaded on GC's memory
     * @return true if loaded, false otherwise
     */
    inline bool isGcLoaded() const { return m_isGcLoaded; }

    /**
     * Indicates if resource need to be loaded on GC's memory
     * @return true if resource need to be loaded, false otherwise
     */
    inline bool needGcLoad() const { return m_needGcInit; }
};

}
#endif //GANESHENGINE_GHRESOURCE_H