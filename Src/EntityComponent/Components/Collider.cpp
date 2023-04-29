#include "Collider.h"
#include "EntityComponent/Entity.h"

using namespace me;

Collider::Collider()
{
	
}

Collider::~Collider()
{
}

void Collider::start()
{
	std::cout << "\n\nI'm the collider of: " << mEntity->getName() << "\n" << std::endl;
}

void Collider::onCollisionEnter(Entity* other)
{
	//std::cout << "Im " << mEntity->getName() << " and I have collided with " << other->getName() << std::endl;
	mEntity->onCollisionEnter(other);
}

void Collider::onCollisionStay(Entity* other)
{
	//std::cout << "Stay collision\n";
	mEntity->onCollisionStay(other);
}

void Collider::onCollisionExit(Entity* other)
{
	mEntity->onCollisionExit(other);
}