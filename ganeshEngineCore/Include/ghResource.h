#include "ghHeaders.h"
#include "ghSystem.h"

namespace ganeshEngine {

    using namespace std;

    class Dummy {
    public:
        int m_foo;
        float m_bar;

        Dummy(int foo, float bar) : m_foo(foo), m_bar(bar) {
        }

        virtual ~Dummy() {
        }
    };

    class IResource {
    protected:
        U32 m_resourceId;
    };

/**
 *
 */
    template<typename T>
    class Resource : public IResource {
    private:
        unique_ptr<T> m_object;

    public:

        Resource(unique_ptr<T> obj) : m_object(move(obj)) {
        }

        virtual ~Resource();

        /**
         * The pointer returned should never be copied, stored or deleted
         * @return
         */
        const T *const get() {
            return m_object.get();
        }
    };

    template<typename T>
    using hResource = shared_ptr<Resource<T>>;

/**
 *
 */
    class ResourceConfiguration {
    };

/**
 *
 */
    class ResourceManager : public System<ResourceManager> {
        friend class System<ResourceManager>;

    private:
        unique_ptr<ResourceConfiguration> m_configuration;

        map<int, shared_ptr<IResource>> m_resourcesMap;

    private:
        // temporary empty constructor

        ResourceManager() {
        }

        ResourceManager(unique_ptr<ResourceConfiguration> conf)
                : m_configuration(move(conf)) {
        }

    public:
        ResourceManager(const ResourceManager &) = delete;

        ResourceManager &operator=(const ResourceManager &) = delete;

        virtual ~ResourceManager() {
        }

        template<typename T>
        hResource<T> getResource(int resId) {
            return nullptr;
        }

    protected:
        void vInitialize();

        void vDestroy();
    };

    extern ResourceManager &(*gResource)();
}