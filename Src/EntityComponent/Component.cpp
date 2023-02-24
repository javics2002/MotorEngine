#include "Component.h"

namespace me {

	Component::Component() :
		entity_(nullptr) {
	};

	inline void Component::setEntity(Entity* e) {
		entity_ = e;
	};

	inline Entity* Component::getEntity() {
		return entity_;
	};

};