#include <ecs/ghGameObject.hpp>

namespace ganeshEngine {

RTTI_IMPL_BASE(GameObject)

GameObject::GameObject(U32 uid) :
		mUID(uid),
		mOwnerWorld(nullptr) {}

GameObject::~GameObject() {}

U32 GameObject::getUID() const { return mUID; }

bool GameObject::write(IStream &stream) const {
	return false;
}

bool GameObject::read(IStream &stream) {
	return false;
}

}