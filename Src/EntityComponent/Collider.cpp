#include "Collider.h"


me::Collider::Collider()
{
}

me::Collider::~Collider()
{
}

void me::Collider::onCollisionEnter(Entity* other)
{
	mEntity->OnCollisionEnter(other);
}

void me::Collider::onCollisionStay(Entity* other)
{
	mEntity->OnCollisionStay(other);
}

void me::Collider::onCollisionExit(Entity* other)
{
	mEntity->OnCollisionExit(other);
}