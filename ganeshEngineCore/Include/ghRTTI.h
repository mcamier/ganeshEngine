#ifndef GANESHENGINE_GHRTTI_H
#define GANESHENGINE_GHRTTI_H

#include "ghHeaders.h"
#include "ghStringId.h"
#include <string>

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
#ifndef RTTI_DEF_BASE
#define RTTI_DEF_BASE(name) \
    const RTTI name::rtti(#name);
#endif //RTTI_DEF_BASE


/**
 * Facility for rtti definition of a derived class
 */
#ifndef RTTI_DEF
#define RTTI_DEF(name, parent) \
    const RTTI name::rtti(#name, &parent::rtti);
#endif //RTTI_DEF

namespace ganeshEngine {

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
    const std::string value;

    /** RTTI object pointer of the base class */
    const RTTI *mParent;

public:
    explicit RTTI(const char* name);
    explicit RTTI(std::string &name);
    explicit RTTI(const char* name, const RTTI *parent);
    explicit RTTI(std::string &name, const RTTI *parent);

    /**
     * @param other
     * @return true if other is amoung base class of the current one
     */
    bool isDerivedFrom(const RTTI& other) const;

    /**
     * @param other
     * @return true if other rtti and current rtti informations are from the same class
     */
    bool isSame(const RTTI& other) const;
};

}

#endif //GANESHENGINE_GHRTTI_H
