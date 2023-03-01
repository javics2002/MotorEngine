#include "Component.h"
#include "Entity.h"

namespace me {

	Component::Component() :
		mEntity(nullptr) {
	}

	inline void Component::setEntity(Entity* e) {
		mEntity = e;
	}

	inline Entity* Component::getEntity() {
		return mEntity;
	}

	template<typename T>
	T* Component::getComponent()
	{
		return mEntity->getComponent<T>();
	}

};