#include "Component.h"

namespace me {

	Component::Component() :
		mEntity(nullptr)
	{
	};

	Component::~Component() {};

	void Component::start() {};

	void Component::update() {};

	void Component::lateUpdate() {};

	void Component::onCollisionEnter(Entity* other) {};

	void Component::onCollisionStay(Entity* other) {};

	void Component::onCollisionExit(Entity* other) {};

};