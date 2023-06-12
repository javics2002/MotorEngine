#include "Collider.h"
#include "EntityComponent/Entity.h"

using namespace me;

me::Component* me::FactoryCollider::create(Parameters& params)
{
	Collider* collider = new Collider();

	return collider;
}

void me::FactoryCollider::destroy(Component* component)
{
	delete component;
}

Collider::Collider()
{
	
}

Collider::~Collider()
{
}

void Collider::start()
{
}

void Collider::onCollisionEnter(Entity* other)
{
	mEntity->onCollisionEnter(other);
}

void Collider::onCollisionStay(Entity* other)
{
	mEntity->onCollisionStay(other);
}

void Collider::onCollisionExit(Entity* other)
{
	mEntity->onCollisionExit(other);
}