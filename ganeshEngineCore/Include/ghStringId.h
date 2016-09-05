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

static stringId gInternString(const char * value) {
	size_t hash = std::hash<string>{}(value);
	auto&& itr = gInternStrings.find(hash);
	if(itr == gInternStrings.end()) {
		gInternStrings.insert(make_pair(hash, string(value)));
	}
	return hash;
};

static const string& gStringFromStringId(stringId id) {
	static const string noStringFound = "no String Found";
	auto&& itr = gInternStrings.find(id);
	if(itr == gInternStrings.end()) {
		return noStringFound;
	}
	return itr->second;
};

}

#endif //GANESHENGINE_GHSTRINGID_H
