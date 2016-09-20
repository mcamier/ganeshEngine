#include "util/ghRTTI.hpp"

using namespace std;

namespace ganeshEngine {

RTTI::RTTI(const char* name) :
        value(string(name)),
        mParent(nullptr) {}

RTTI::RTTI(std::string &name) :
        value(name),
        mParent(nullptr) {}

RTTI::RTTI(const char* name, const RTTI *parent) :
        value(string(name)),
        mParent(parent) {}

RTTI::RTTI(std::string &name, const RTTI *parent) :
        value(name),
        mParent(parent) {}

bool RTTI::isDerivedFrom(const RTTI& other) const {
    const RTTI *pCompare = this;
    while(pCompare != nullptr) {
        if(pCompare->isSame(other))
            return true;
        pCompare = pCompare->mParent;
    }
    return false;
}

bool RTTI::isSame(const RTTI& other) const {
    return this->value == other.value;
}

}