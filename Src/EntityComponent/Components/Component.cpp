#include "Component.h"

namespace me {

	Component::Component() :
		mEntity(nullptr)
	{
	};

	Component::~Component() {};

	void Component::start() {};

	void Component::update(const double& dt) {};

	void Component::lateUpdate(const double& dt) {};

	void Component::onCollisionEnter(Entity* other) {};

	void Component::onCollisionStay(Entity* other) {};

	void Component::onCollisionExit(Entity* other) {};

};