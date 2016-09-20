#include "ghStringId.h"

namespace ganeshEngine {

stringId gInternString(const char * value) {
	size_t hash = std::hash<string>{}(value);
	map<stringId, string>::const_iterator itr = gInternStrings.find(hash);
	if(itr == gInternStrings.end()) {
		gInternStrings.emplace(pair<stringId, string>(hash, string(value)));
	}
	return hash;
}

const string& gStringFromStringId(stringId id) {
	static const string noStringFound = "no String Found";
	map<stringId, string>::const_iterator itr = gInternStrings.find(id);
	if(itr == gInternStrings.end()) {
		return noStringFound;
	}
	return itr->second;
}

}