#ifndef GANESHENGINE_GHRESOURCEHANDLER_H
#define GANESHENGINE_GHRESOURCEHANDLER_H

#include "ghResourceWrapper.hpp"
#include <util/ghSerializable.hpp>

namespace ganeshEngine {

/**
 * ResourceHandler are user's intermediate to access loaded Resources
 */
template<typename T>
class ResourceHandler {
private:
    /** Pointer to the ResourceWrapper managed by ResourceManager
     * The underlying ResourceWrapper cannot be directly used through this handler, it's to avoid user messing with
     * internal state of an object managed by the ResourceManager
     */
    shared_ptr<ResourceWrapper> m_wrapper;

public:
    ResourceHandler() : m_wrapper(nullptr) {}
    explicit ResourceHandler(shared_ptr <ResourceWrapper> wrapper) : m_wrapper(wrapper) {}

    ResourceHandler(const ResourceHandler &) = default;
    ResourceHandler &operator=(const ResourceHandler &) = default;
/*
    ResourceHandler(ResourceHandler&&) {}
    ResourceHandler &operator=(ResourceHandler&&) {}
*/
    /**
     * Gives direct access to a pointer of the underlying resource
     * @note could return a nullptr in certain conditions
     * @return pointer to const resource
     */
    const T *operator->() {
        return (dynamic_pointer_cast<T>(m_wrapper->getData())).get();
    }

    /**
     * Gives direct access to a pointer of the underlying resource
     * @note could return a nullptr in certain conditions
     * @return pointer to const resource
     */
    const T& operator*() const {
        return (dynamic_pointer_cast<T>(m_wrapper->getData())).get();
    }

    /**
     * @note internal use only
     * @return pointer to const resource
     */
    T * const get() {
        return (dynamic_pointer_cast<T>(m_wrapper->getData())).get();
    }

    ResourceWrapper &operator=(std::nullptr_t ptr) {
        m_wrapper = nullptr;
        return this;
    }

    bool operator==(std::nullptr_t ptr) {
        return m_wrapper.get() == nullptr;
    }

    bool operator!=(std::nullptr_t ptr) {
        return m_wrapper.get() != nullptr;
    }

    const string& getName() const {
        static string putain = "putain";
        return putain;
    }

    const stringId getId() const {
        return m_wrapper->getId();
    }
};

}

#endif //GANESHENGINE_GHRESOURCEHANDLER_H
