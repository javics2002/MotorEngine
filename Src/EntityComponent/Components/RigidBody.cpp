#include "RigidBody.h"

#include "LinearMath/btTransform.h"
#include "LinearMath/btQuaternion.h"
#include "LinearMath/btVector3.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

#include "Physics/PhysicsManager.h"

#include "EntityComponent/Entity.h"

me::RigidBody::RigidBody()
{

}

me::RigidBody::~RigidBody()
{
}

void me::RigidBody::start()
{

	mTransform = mEntity->getComponent<Transform>("transform");
	
	assert(mTransform && "An Entity doesn't have the transform component");

	mBtTransform = new btTransform(btQuaternion(mTransform->getRotation().getRotationInBullet()), btVector3(mTransform->getPosition().v3ToBulletV3()));

	btVector3 scale = mTransform->getScale().v3ToBulletV3();

	mBtRigidBody = me::physicsManager().createRigidBody(mBtTransform, scale, Shapes(mColShape),
		MovementType(mMvType), mIsTrigger, mFricion, mMass, mRestitution);

	mBtRigidBody->setUserPointer(this);
	
}

//To implement
void me::RigidBody::update()
{
	if (MovementType(mMvType) != MOVEMENT_TYPE_STATIC) {
		btVector3 pos = mBtRigidBody->getWorldTransform().getOrigin();
		mTransform->setPosition(Vector3(pos.x(), pos.y(), pos.z()));
	}
}

//To implement
void me::RigidBody::lateUpdate()
{
}

void me::RigidBody::setTrigger(bool isTrigger)
{
	mIsTrigger = isTrigger;
}

void me::RigidBody::setMass(float mass)
{
	mMass = mass;
}

void me::RigidBody::setFriction(float friction)
{
	mFricion = friction;
}

void me::RigidBody::setRestitution(float restitution)
{
	mRestitution = restitution;
}

void me::RigidBody::setColShape(int colShape)
{
	mColShape = colShape;
}

void me::RigidBody::setMomeventType(int mvType)
{
	mMvType = mvType;
}

void me::RigidBody::addForce(Vector3 force, Vector3 relativePos)
{
	mBtRigidBody->applyForce(force.v3ToBulletV3(), relativePos.v3ToBulletV3());
}

void me::RigidBody::addImpulse(Vector3 impulse, Vector3 relativePos)
{
	mBtRigidBody->applyImpulse(impulse.v3ToBulletV3(), relativePos.v3ToBulletV3());
}

bool me::RigidBody::getTrigger()
{
	return mIsTrigger;
}

float me::RigidBody::getMass() {
	return mMass;
}

float me::RigidBody::getFriction()
{
	return mFricion;
}

float me::RigidBody::getRestitution()
{
	return mRestitution;
}

int me::RigidBody::getColShape()
{
	return mColShape;
}

int me::RigidBody::getMovementType()
{
	return mMvType;
}
