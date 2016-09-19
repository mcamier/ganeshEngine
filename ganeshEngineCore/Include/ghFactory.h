#ifndef GANESHENGINE_GHFACTORY_H
#define GANESHENGINE_GHFACTORY_H

#include "ghHeaders.h"

#include <map>
#include <memory>

#ifndef CREATOR_IMPL
#define CREATOR_IMPL(className) \
    template<> class ICreator<className> { \
    public: \
        className* create(U32 id) const {\
            return new className(id);\
        }\
    };\
    gRegisterComponentFactory(#className, new ICreator<>(className));
#endif //REGISTER_CREATOR


namespace ganeshEngine {

/**
 *
 */
template<typename T>
class ICreator {
public:
    virtual T* create(U32 id) const = 0;
};

map<stringId, ICreator*> gComponentFactories = map<stringId, ICreator*>();

Component* gCreateInstance(const char* className) {
    auto itr = gComponentFactories.find(typeName);
    if(itr != gComponentFactories.end()) {
        return itr->second->create();
    }
    return nullptr;
}


Component* gRegisterComponentFactory(const char* typeName, ICreator* creator) {
    if(gComponentFactories.find(typeName) != gComponentFactories.end()) {
        gComponentFactories.insert(make_pair(typeName, creator));
    }
}

}

#endif //GANESHENGINE_GHFACTORY_H
