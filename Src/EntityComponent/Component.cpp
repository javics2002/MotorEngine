#include "Component.h"
#include "Entity.h"

namespace me {

	Component::Component() :
		mEntity(nullptr)
	{
	};

	Component::~Component() {};

	void Component::start() {};

	void Component::update() {};

	void Component::lateUpdate() {};

	void Component::OnCollisionEnter(Entity* other) {};

	void Component::OnCollisionStay(Entity* other) {};

	void Component::OnCollisionExit(Entity* other) {};

};