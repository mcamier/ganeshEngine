#include "util/ghRTTI.hpp"

using namespace std;

namespace ganeshEngine {

RTTI::RTTI(std::string &name) :
        value(name),
        mParent(nullptr) {}

RTTI::RTTI(std::string &name, const RTTI *parent) :
        value(name),
        mParent(parent) {}

RTTI::RTTI(const char* name) :
        value(std::string(name)),
        mParent(nullptr) {}

RTTI::RTTI(const char* name, const RTTI *parent) :
        value(std::string(name)),
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
    return this->value.compare(other.value) == 0;
}

std::string RTTI::getClassName() const {
    return this->value;
}

}