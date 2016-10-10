#ifndef GANESHENGINE_GHRTTI_H
#define GANESHENGINE_GHRTTI_H

#include <string>
#include <ghTypes.hpp>
#include <map>

/**
 * Facility for rtti declaration
 */
#ifndef RTTI_DECL
#define RTTI_DECL() \
    public: \
        virtual const RTTI& getRTTI() const { return rtti; } \
        static const RTTI rtti; \
    private:
#endif //RTTI_DECL


/**
 * Facility for rtti definition of a base class
 */
#ifndef RTTI_IMPL_BASE
#define RTTI_IMPL_BASE(name) \
    const RTTI name::rtti(#name);

#endif //RTTI_IMPL_BASE


/**
 * Facility for rtti definition of a derived class
 */
#ifndef RTTI_IMPL
#define RTTI_IMPL(name, parent) \
    const RTTI name::rtti(#name, &parent::rtti);\
    template<> RTTIFactory::Creator_t* RTTIFactory::Register<name>::creator = RTTIFactory::Register<name>::init_creator(#name);
#endif //RTTI_IMPL


/**
 * Facility for rtti definition of a abstract derived class
 */
#ifndef RTTI_ABSTRACT_IMPL
#define RTTI_ABSTRACT_IMPL(name, parent) \
    const RTTI name::rtti(#name, &parent::rtti);
#endif //RTTI_ABSTRACT_IMPL

namespace ganeshEngine {

//forward declaration
class GameObject;

/**
 * Store informations about a class and provides them during runtime.
 * The informations available are : the name of the class and a pointer to RTTI informations of the base class if it
 * exists
 *
 * @note At this time only supports single inheritance rtti informations
 */
class RTTI {
private:
    /** Name of the class */
    std::string value;

    /** RTTI object pointer of the base class */
    const RTTI *mParent;

public:
    explicit RTTI(std::string& name);
    explicit RTTI(std::string& name, const RTTI *parent);
    explicit RTTI(const char* name);
    explicit RTTI(const char* name, const RTTI *parent);

    /**
     * Returns true if the correspondant class is derived from the class correspondant of the passed
     *
     * @param other rtti to compare with
     * @return true if other is amoung base class of the current one
     */
    bool isDerivedFrom(const RTTI& other) const;

    /**
     * Return true if the correspondant class is exactly the same as the class correspondant of the passed
     * @param other rtti to compare with
     * @return true if other rtti and current rtti informations are from the same class
     */
    bool isSame(const RTTI& other) const;

    /**
     * Return the name of the correspondant class
     * @return the of the correspondant class
     */
    std::string getClassName() const;
};


struct RTTIFactory {
    static GameObject* create(const RTTI& rtti, U32 id) {
        return create(rtti.getClassName(), id);
    }

    static GameObject* create(const RTTI& rtti) {
        return create(rtti.getClassName());
    }

    static GameObject* create(const std::string& name, U32 id) {
        const Creators_t::const_iterator iter = static_creators().find(name);
        return iter == static_creators().end() ? nullptr : (*iter->second)(id);
    }

    static GameObject* create(const std::string& name) {
        const Creators_t::const_iterator iter = static_creators().find(name);
        return iter == static_creators().end() ? nullptr : (*iter->second)(gGetNextId());
    }

private:
    typedef GameObject* Creator_t(U32 id);
    typedef std::map<std::string, Creator_t*> Creators_t;

    static Creators_t& static_creators() {
        static Creators_t s_creators;
        return s_creators;
    }

    template<class T> struct Register {
        static Creator_t* creator;

        static Creator_t* init_creator(const std::string& name) {
            return static_creators()[name] = create;
        }

        static GameObject* create(U32 id) {
            return new T(id);
        };
    };
};

}

#endif //GANESHENGINE_GHRTTI_H
