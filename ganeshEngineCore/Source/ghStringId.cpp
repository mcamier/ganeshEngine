#include "ghStringId.h"

namespace ganeshEngine {


stringId gInternString(const char * value) {
	size_t hash = std::hash<string>{}(value);
	auto&& itr = gInternStrings.find(hash);
	if(itr == gInternStrings.end()) {
		gInternStrings.insert(make_pair(hash, string(value)));
	}
	return hash;
}

const string& gStringFromStringId(stringId id) {
	static const string noStringFound = "no String Found";
	auto&& itr = gInternStrings.find(id);
	if(itr == gInternStrings.end()) {
		return noStringFound;
	}
	return itr->second;
}

}