#include "RigidBody.h"

#include "LinearMath/btTransform.h"
#include "LinearMath/btQuaternion.h"
#include "LinearMath/btVector3.h"

#include "Bullet/PhysicsManager.h"

#include "Entity.h"

me::RigidBody::RigidBody(int colShape, int mvType, float mass, float friction, float restitution, bool isTrigger)
{
	mColShape = colShape;
	mMvType = mvType;
	mMass = mass;
	mFricion = friction;
	mIsTrigger = isTrigger;
	mRestitution = restitution;
}

me::RigidBody::~RigidBody()
{
}

void me::RigidBody::start()
{

	mTransform = mEntity->getComponent<Transform>();

	mBtTransform = new btTransform(btQuaternion(mTransform->getRotationInBullet()), btVector3(mTransform->getPosition().v3ToBulletV3()));

	scale = mTransform->getScale().v3ToBulletV3();

	mBtRigidBody = pm().createRigidBody(mBtTransform, &scale, Shapes(mColShape),
		MovementType(mMvType), mIsTrigger, mFricion, mMass, mRestitution);
	
}

//To implement
void me::RigidBody::update()
{
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

void me::RigidBody::addForce(Vector3 force, Vector3 relativePos)
{
	mBtRigidBody->applyForce(force.v3ToBulletV3(), relativePos.v3ToBulletV3());
}

void me::RigidBody::addImpulse(Vector3 impulse, Vector3 relativePos)
{
	mBtRigidBody->applyImpulse(impulse.v3ToBulletV3(), relativePos.v3ToBulletV3());
}

float me::RigidBody::getMass()
{
	return mMass;
}
