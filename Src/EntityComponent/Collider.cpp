#include "Collider.h"

me::Collider::Collider()
{
}

me::Collider::~Collider()
{
}

void me::Collider::onCollisionEnter(Entity* other)
{
	entity_->OnCollisionEnter(other);
}

void me::Collider::onCollisionStay(Entity* other)
{
	entity_->OnCollisionStay(other);
}

void me::Collider::onCollisionExit(Entity* other)
{
	entity_->OnCollisionExit(other);
}
