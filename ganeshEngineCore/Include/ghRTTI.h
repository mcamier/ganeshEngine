#ifndef GANESHENGINE_GHRTTI_H
#define GANESHENGINE_GHRTTI_H

#include "ghHeaders.h"
#include "ghStringId.h"
#include <string>

#ifndef RTTI_DECL
#define RTTI_DECL() \
    public: \
        virtual const RTTI& getRTTI() const { return rtti; } \
        static const RTTI rtti; \
    private:
#endif //RTTI_DECL

#ifndef RTTI_DEF_BASE
#define RTTI_DEF_BASE(name) \
    const RTTI name::rtti(#name);
#endif //RTTI_DEF_BASE

#ifndef RTTI_DEF
#define RTTI_DEF(name, parent) \
    const RTTI name::rtti(#name, &parent::rtti);
#endif //RTTI_DEF

namespace ganeshEngine {

/**
 * At this time only supports single inheritance rtti informations
 */
class RTTI {
private:
    const std::string value;
    const RTTI *mParent;

public:
    explicit RTTI(const char* name);
    explicit RTTI(std::string &name);
    explicit RTTI(const char* name, const RTTI *parent);
    explicit RTTI(std::string &name, const RTTI *parent);

    bool isDerivedFrom(const RTTI& other) const;

    bool isSame(const RTTI& other) const;
};

}

#endif //GANESHENGINE_GHRTTI_H
