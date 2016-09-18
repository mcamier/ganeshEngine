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
    };
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


template<typename T>
class Factory {
    typedef map<stringId, unique_ptr<ICreator<T>>> creatorMap_t;

private:
    creatorMap_t mCreatorMap;

public:
    Factory() :
            mCreatorMap(creatorMap_t()) {}

    /**
     * @note you can only register a creator with a give name once, call the method twice with the same stringId will
     * do nothing
     *
     * @param typeName
     * @param creator
     */
    void registerCreator(stringId typeName, unique_ptr<ICreator<T>> creator) {
        if(mCreatorMap.find(typeName) != mCreatorMap.end()) {
            mCreatorMap.insert(make_pair(typeName, creator));
        }
    }

    /**
     *
     * @param typeName
     */
    void unregisterCreator(stringId typeName) {
        auto itr = mCreatorMap.find(typeName);
        if(itr != mCreatorMap.end()) {
            mCreatorMap.erase(itr);
        }
    }

    /**
     *
     * @param typeName
     * @return
     */
    unique_ptr<T> create(stringId typeName) {
        auto itr = mCreatorMap.find(typeName);
        if(itr != mCreatorMap.end()) {
            return unique_ptr<T>(itr->second->create());
        }
        return nullptr;
    }
};

}

#endif //GANESHENGINE_GHFACTORY_H
