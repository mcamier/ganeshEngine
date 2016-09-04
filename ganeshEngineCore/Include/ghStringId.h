#ifndef GANESHENGINE_GHSTRINGID_H
#define GANESHENGINE_GHSTRINGID_H

#include <map>
#include <string>

using namespace std;

namespace ganeshEngine {

    using stringId = size_t;

    static map<stringId, string> gInternalStrings = map<stringId, string>();

    static stringId gInternString(const char* value);

    static const string& gGetInternString(stringId hashId);

}

#endif //GANESHENGINE_GHSTRINGID_H
