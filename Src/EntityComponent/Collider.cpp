#include "Collider.h"


me::Collider::Collider()
{
}

me::Collider::~Collider()
{
}

void me::Collider::onCollisionEnter(Entity* other)
{
	//std::cout << "Im " << mEntity->getName() << " and I have collided with " << other->getName() << std::endl;
	mEntity->OnCollisionEnter(other);
}

void me::Collider::onCollisionStay(Entity* other)
{
	//std::cout << "Stay collision\n";
	mEntity->OnCollisionStay(other);
}

void me::Collider::onCollisionExit(Entity* other)
{
	mEntity->OnCollisionExit(other);
}