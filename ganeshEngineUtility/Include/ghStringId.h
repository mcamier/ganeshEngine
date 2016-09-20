#ifndef GANESHENGINE_GHSTRINGID_H
#define GANESHENGINE_GHSTRINGID_H

#include <map>
#include <string>
#include <functional>

namespace ganeshEngine {

using namespace std;

/**
 * stringId is used to create id's corresponding to given strings
 */
using stringId = size_t;

static map<stringId, string> gInternStrings = map<stringId, string>();

stringId gInternString(const char * value);

const string& gStringFromStringId(stringId id);

}

#endif //GANESHENGINE_GHSTRINGID_H
