#ifndef GANESHENGINE_GHSYSTEM_H
#define GANESHENGINE_GHSYSTEM_H

#include "ghHeaders.h"

namespace ganeshEngine {

using namespace std;

enum SystemState {
    UNINITIALIZED = 0x01,
    INITIALIZED = 0x02,
    DESTROYED = 0x04,
};

/** System class meant to be used as global services providers, they are singletons required
 *  to be initialized within the Application's initialization and destroyed within Application's
 *  destruction.
 *  They must be global accessible through the entire application
 *
 *  The main Application is also an instance of System, it is the system that rules them all...
 *
 */
template<typename T>
class System {

public:

    /** Getter to specific system reference
     *
     * \return Reference top the specific system
     */
    static T& get() {
        ASSERT(_instance != nullptr);
        ASSERT_FLAG(_state(), INITIALIZED);
        return *_instance();
    }

    /** Create and initialize the specific System singleton
     *
     * \param[in] Variadic arguments list forwarded to the system specific constructor
     */
    template<typename... Args>
    static void Initialize(Args... args) {
        static_assert(std::is_base_of<System, T>::value, "Type T must be derivated from System");

        if( (_state() & UNINITIALIZED) == UNINITIALIZED ) {
            ASSERT(_instance() == nullptr);

            _instance() = new T(std::forward<Args>(args)...);
            ((System*) _instance())->vInitialize();
            _state() = INITIALIZED;
        }
    }

    /** Destroy the specific system and release its memory
     */
    static void Destroy() {
        ASSERT_FLAG(_state(), INITIALIZED);

        ((System*) _instance())->vDestroy();
        delete _instance();
        _instance() = nullptr;
        _state() = DESTROYED;
    }

protected:
    static T*& _instance() {
        static T* instance = nullptr;
        return instance;
    }

    static SystemState& _state() {
        static SystemState state = UNINITIALIZED;
        return state;
    }

    virtual void vInitialize() {}
    virtual void vDestroy() {}
};

}

#endif //GANESHENGINE_GHSYSTEM_H
