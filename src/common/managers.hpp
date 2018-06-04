#ifndef RENDERENGINEPLAYGROUND_SERVICE_INIT_HPP
#define RENDERENGINEPLAYGROUND_SERVICE_INIT_HPP

#include "common.hpp"

#include <type_traits>
#include <utility>
#include <cstdint>

namespace rep
{

/**
 * Enumerate the different status a manager could have
 */
enum ManagerState
{
    UNINITIALIZED = 0x01,
    INITIALIZED = 0x02,
    DESTROYED = 0x04
};


template<typename T>
class Singleton
{
protected:
    /**
     * Internal getter of the reference of the static instance pointer
     *
     * @return reference to the static instance pointer
     */
    static T *&_instance()
    {
        static T *instance = nullptr;
        return instance;
    }

    /**
     * Internal getter of the reference of the static state
     *
     * @return reference to the static state
     */
    static ManagerState &_state()
    {
        static ManagerState state = UNINITIALIZED;
        return state;
    }

public:
    /**
     * Getter to specific system reference
     *
     * @warning if DEBUG_ASSERTION_ENABLED is defined this call will raise a breakpoint if the internal
     * instance pointer points to nullptr or the system state is not INITIALIZED.
     *
     * @return Reference to the specific system instance
     */
    static T &get()
    {
        ASSERT(_instance() != nullptr);
        ASSERT_FLAG(_state(), INITIALIZED);
        return *_instance();
    }
};


/**
*  Manager classes meant to be used as global services providers, they are singletons and requires
*  to be initialized within the Application's initialization and destroyed within Application's
*  destruction.
*  They could must accessed through the entire application
*
*  A class extending Singleton should removed its copy constructor and its assigment operator
*  Furthermore, its constructor should be private or private as a semantic requirement
*/
template<typename T, typename INIT_T>
class Manager :
        public Singleton<T>
{
public:
    static void initialize(INIT_T initStructArg)
    {
        static_assert(std::is_base_of<Manager, T>::value, "Type T must be derivated from Manager");

        if ((Singleton<T>::_state() & UNINITIALIZED) == UNINITIALIZED)
        {
            ASSERT(Singleton<T>::_instance() == nullptr);

            Singleton<T>::_instance() = new T();
            ((Manager *) Singleton<T>::_instance())->vInit(std::forward<INIT_T>(initStructArg));
            Singleton<T>::_state() = INITIALIZED;
        }
    }


    static void destroy()
    {
        ASSERT_FLAG(Singleton<T>::_state(), INITIALIZED);

        ((Manager *) Singleton<T>::_instance())->vDestroy();
        delete Singleton<T>::_instance();
        Singleton<T>::_instance() = nullptr;
        Singleton<T>::_state() = DESTROYED;
    }


protected:
    virtual void vInit(INIT_T initStructArg) = 0;

    virtual void vDestroy() = 0;

    virtual void vUpdate() = 0;

};

}

#endif //RENDERENGINEPLAYGROUND_SERVICE_INIT_HPP
