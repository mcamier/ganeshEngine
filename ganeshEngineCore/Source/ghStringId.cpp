#include "ghStringId.h"

#include <functional>
#include "ghHeaders.h"

namespace ganeshEngine {

    stringId ghInternString(const char* value) {
        stringId hashValue = hash<string>{}(value);
        ASSERT(hashValue>0);

        auto&& itr = gInternalStrings.find(hashValue);
        if(itr == gInternalStrings.end()) {
            gInternalStrings.insert(make_pair(hashValue, string(value)));
        }
        return hashValue;
    }

    const string& gGetInternString(stringId stringId) {
        static string noStringFound = "no string found";
        ASSERT(stringId>0);

        auto&& itr = gInternalStrings.find(stringId);
        if(itr == gInternalStrings.end()) {
            return itr->second;
        }
        return noStringFound;
    }
}