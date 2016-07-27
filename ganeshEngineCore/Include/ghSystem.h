#ifndef GANESHENGINE_GHSYSTEM_H
#define GANESHENGINE_GHSYSTEM_H

#include "ghHeaders.h"

namespace ganeshEngine {

    using namespace std;

/**
 * Used to describe the current state of a system
 */
    enum SystemState {
        UNINITIALIZED = 0x01,
        INITIALIZED = 0x02,
        DESTROYED = 0x04,
    };

/**
 *  System classes meant to be used as global services providers, they are singletons and requires
 *  to be initialized within the Application's initialization and destroyed within Application's
 *  destruction.
 *  They could must accessed through the entire application
 */
    template<typename T>
    class System {
    public:

        /**
         * Getter to specific system reference
         *
         * @warning if DEBUG_ASSERTION_ENABLED is defined this call will raise a breakpoint if the internal
         * instance pointer points to nullptr or the system state is not INITIALIZED.
         *
         * @return Reference to the specific system instance
         */
        static T &get() {
            ASSERT(_instance != nullptr);
            ASSERT_FLAG(_state(), INITIALIZED);
            return *_instance();
        }

        /**
         * Create and initialize the specific System singleton
         *
         * @warning if DEBUG_ASSERTION_ENABLED is defined this call will raise a breakpoint if the internal
         * instance pointer doesn't points to nullptr while the system state is UNINITIALIZED.
         *
         * @param args Variadic arguments list forwarded to the system specific constructor
         */
        template<typename... Args>
        static void Initialize(Args... args) {
            static_assert(std::is_base_of<System, T>::value, "Type T must be derivated from System");

            if ((_state() & UNINITIALIZED) == UNINITIALIZED) {
                ASSERT(_instance() == nullptr);

                _instance() = new T(std::forward<Args>(args)...);
                ((System *) _instance())->vInitialize();
                _state() = INITIALIZED;
            }
        }

        /**
         * Destroy the specific system and release its memory
         *
         * @warning if DEBUG_ASSERTION_ENABLED is defined this call will raise a breakpoint if the internal
         * intance pointer doesn't points to nullptr while the system state is UNINITIALIZED.
         */
        static void Destroy() {
            ASSERT_FLAG(_state(), INITIALIZED);

            ((System *) _instance())->vDestroy();
            delete _instance();
            _instance() = nullptr;
            _state() = DESTROYED;
        }

    protected:

        /**
         * Internal getter of the reference of the static instance pointer
         *
         * @return reference to the static instance pointer
         */
        static T *&_instance() {
            static T *instance = nullptr;
            return instance;
        }

        /**
         * Internal getter of the reference of the static state
         *
         * @return reference to the static state
         */
        static SystemState &_state() {
            static SystemState state = UNINITIALIZED;
            return state;
        }

        /**
         * Initialize method called by the static initialization method
         */
        virtual void vInitialize() {
        }

        /**
         * Destroy method called by the static initialization method
         */
        virtual void vDestroy() {
        }
    };

}

#endif //GANESHENGINE_GHSYSTEM_H
