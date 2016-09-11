#ifndef GANESHENGINE_GHRESOURCEUTIL_H
#define GANESHENGINE_GHRESOURCEUTIL_H

#include "ghHeaders.h"
#include "ghStringId.h"

#include <map>

namespace ganeshEngine{

using namespace std;

/**
 *
 */
class resourceMetadata {
public:
    resourceMetadata() {}
    ~resourceMetadata() {}

    stringId name;

    union value_u {
        F64 asDouble;
        U32 asUInt;
        const char* asString;
        bool asBool;
    } value;

};

/**
 *
 */
class resourceEntry {
public:
    resourceEntry() {}
    ~resourceEntry() {}

    string name;
    string filename;
    string loaderName;
    bool eagerLoading;
    map<stringId, resourceMetadata> metadatas;
    map<stringId, stringId> dependencies;
};

/**
 *
 */
class ResourceInfos {
private:
    string mName;
    string mFilename;
    map<stringId, resourceMetadata> mMetadatas;
    map<stringId, stringId> mDependencies;

public:
    ResourceInfos(const string& name) :
            mName(name),
            mFilename(""),
            mMetadatas(map<stringId, resourceMetadata>()),
            mDependencies(map<stringId, stringId>()) {}

    ResourceInfos(const string& name, const string& filename, map<stringId, resourceMetadata>& metadata, map<stringId, stringId>& dependencies) :
            mName(name),
            mFilename(filename),
            mMetadatas(move(metadata)),
            mDependencies(move(dependencies)) {}

    ~ResourceInfos() {}

    const string& getName() const {
        return mName;
    }

    const string& getFilename() const {
        return mFilename;
    }

    const map<stringId, stringId>& getDependencies() const {
        return mDependencies;
    }

    const map<stringId, resourceMetadata>& getMetadatas() const {
        return mMetadatas;
    }
};

}

#endif //GANESHENGINE_GHRESOURCEUTIL_H
