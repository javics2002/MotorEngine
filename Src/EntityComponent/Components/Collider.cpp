#include "Collider.h"
#include "EntityComponent/Entity.h"

me::Collider::Collider()
{
	
}

me::Collider::~Collider()
{
}

void me::Collider::start()
{
	std::cout << "\n\nI'm the collider of: " << mEntity->getName() << "\n" << std::endl;
}

void me::Collider::onCollisionEnter(Entity* other)
{
	std::cout << "Im " << mEntity->getName() << " and I have collided with " << other->getName() << std::endl;
	mEntity->onCollisionEnter(other);
}

void me::Collider::onCollisionStay(Entity* other)
{
	//std::cout << "Stay collision\n";
	mEntity->onCollisionStay(other);
}

void me::Collider::onCollisionExit(Entity* other)
{
	mEntity->onCollisionExit(other);
}