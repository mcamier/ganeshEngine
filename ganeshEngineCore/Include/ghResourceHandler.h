#ifndef GANESHENGINE_GHRESOURCEHANDLER_H
#define GANESHENGINE_GHRESOURCEHANDLER_H

namespace ganeshEngine {

/**
 * ResourceHandler are user's intermediate to access loaded Resources
 */
template<typename T>
class ResourceHandler {
private:
    /** Pointer to the ResourceWrapper managed by ResourceManager */
    shared_ptr<ResourceWrapper> m_wrapper;

public:
    explicit ResourceHandler(shared_ptr <ResourceWrapper> wrapper) : m_wrapper(wrapper) {}

    /**
     * Gives direct access to a pointer of the underlying resource
     * @note could return a nullptr in certain conditions
     * @return pointer to const resource
     */
    const T *operator->() {
        return (dynamic_pointer_cast<T>(m_wrapper->getData())).get();
    }
};

}

#endif //GANESHENGINE_GHRESOURCEHANDLER_H
