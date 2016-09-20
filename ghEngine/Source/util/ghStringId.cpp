#include "util/ghStringId.hpp"

namespace ganeshEngine {

map<stringId, string>* gInternStrings = nullptr;

stringId gInternString(const char * value) {
	if(gInternStrings == nullptr) {
		gInternStrings = new map<stringId, string>();
	}

	size_t hash = std::hash<string>{}(value);
	map<stringId, string>::const_iterator itr = gInternStrings->find(hash);
	if(itr == gInternStrings->end()) {
		gInternStrings->insert(pair<stringId, string>(hash, string(value)));
	}
	return hash;
}

const string& gStringFromStringId(stringId id) {
	static const string noStringFound = "no String Found";
	map<stringId, string>::const_iterator itr = gInternStrings->find(id);
	if(itr == gInternStrings->end()) {
		return noStringFound;
	}
	return itr->second;
}

}