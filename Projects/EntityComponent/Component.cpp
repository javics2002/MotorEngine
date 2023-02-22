#include "Component.h"

namespace me {

	inline void Component::setEntity(Entity* e) {
		entity_ = e;
	}

	inline Entity* Component::getEntity() {
		return entity_;
	}

};