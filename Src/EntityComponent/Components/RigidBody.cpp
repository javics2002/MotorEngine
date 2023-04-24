#include "RigidBody.h"

#include "LinearMath/btTransform.h"
#include "LinearMath/btQuaternion.h"
#include "LinearMath/btVector3.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

#include "Physics/PhysicsManager.h"
#include "EntityComponent/Entity.h"

using namespace me;

RigidBody::RigidBody()
{

}

RigidBody::~RigidBody()
{
	physicsManager().destroyRigidBody(mBtRigidBody);
	mBtRigidBody = nullptr;
	delete mBtTransform;
}

void RigidBody::start()
{
	mTransform = mEntity->getComponent<Transform>("transform");
	
	assert(mTransform && "An Entity doesn't have the transform component");

	mBtTransform = new btTransform(btQuaternion(mTransform->getRotation().getRotationInBullet()), btVector3(mTransform->getPosition().v3ToBulletV3()));

	btVector3 scale = mTransform->getScale().v3ToBulletV3();
	btVector3 colliderScale = mColliderScale.v3ToBulletV3();

	mBtRigidBody = me::physicsManager().createRigidBody(mBtTransform, scale, colliderScale,  mGroup, mMask, mColShape,
										mMvType, mIsTrigger, mFricion, mMass, mRestitution);

	mCollider = mEntity->getComponent<Collider>("collider");

	assert(mCollider && "An Entity doesn't have the collider  component");

	mBtRigidBody->setUserPointer(mCollider);

}

void RigidBody::update(const double& dt)
{
	if (MovementType(mMvType) == MOVEMENT_TYPE_KINEMATIC) {
		
		btTransform btTr = mBtRigidBody->getWorldTransform();
		btTr.setOrigin(mTransform->getPosition().v3ToBulletV3());
		btTr.setRotation(mTransform->getRotation().getRotationInBullet());
		//update the position and rotation of the bullet rigidbody 
		mBtRigidBody->setWorldTransform(btTr);

	}

	if (MovementType(mMvType) == MOVEMENT_TYPE_DYNAMIC) {
		btVector3 pos = mBtRigidBody->getWorldTransform().getOrigin();
		btVector3 vel= mBtRigidBody->getLinearVelocity();
		btQuaternion rot = mBtRigidBody->getWorldTransform().getRotation();
		//update transform position and rotation
		mTransform->setPosition(Vector3(pos.x(), pos.y(), pos.z()));
		mTransform->setVelocity(Vector3(vel.x(), vel.y(), vel.z()));
		mTransform->setRotation(Vector4(rot.x(), rot.y(), rot.z(), rot.w()));
		mBtRigidBody->activate(true);
	}
}

//To implement
void RigidBody::lateUpdate(const double& dt)
{
}

void RigidBody::setTrigger(bool isTrigger)
{
	mIsTrigger = isTrigger;
	if (mBtRigidBody != nullptr) {
		//keeps the previous flags and adds NO_CONTACT_RESPONSE
		if (isTrigger) {
			mBtRigidBody->setCollisionFlags(mBtRigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		}
		//keeps the previous flags and removes NO_CONTACT_RESPONSE
		else mBtRigidBody->setCollisionFlags(mBtRigidBody->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}
}

void RigidBody::setMass(float mass)
{
	mMass = mass;
}

void RigidBody::setFriction(float friction)
{
	mFricion = friction;
	if (mBtRigidBody != nullptr) mBtRigidBody->setFriction(friction);
}

void RigidBody::setRestitution(float restitution)
{
	mRestitution = restitution;
	if(mBtRigidBody != nullptr) mBtRigidBody->setRestitution(restitution);
}

void RigidBody::setColliderScale(Vector3 colliderScale)
{
	mColliderScale = colliderScale;
}

void RigidBody::setColShape(Shapes colShape)
{
	mColShape = colShape;
}

void RigidBody::setMomeventType(MovementType mvType)
{
	if (mBtRigidBody != nullptr) {
		//keeps the previous flags and removes the old movement to add the new one
		mBtRigidBody->setCollisionFlags(mBtRigidBody->getCollisionFlags() & ~mvType);
		mBtRigidBody->setCollisionFlags(mBtRigidBody->getCollisionFlags() | mvType);
	}
	mMvType = mvType;
}

void me::RigidBody::setMask(int mask)
{
	mMask = mask;
	if(mBtRigidBody != nullptr){
		btBroadphaseProxy* bdProxy = mBtRigidBody->getBroadphaseProxy();
		bdProxy->m_collisionFilterMask = mask;
	}
}

void me::RigidBody::setGroup(int group)
{
	mGroup = group;
	if (mBtRigidBody != nullptr) {
		btBroadphaseProxy* bdProxy = mBtRigidBody->getBroadphaseProxy();
		bdProxy->m_collisionFilterGroup = group;
	}
}

void me::RigidBody::addForce(Vector3 force)
{
	btVector3 v = force.v3ToBulletV3();
	mBtRigidBody->applyCentralForce(v);
	mBtRigidBody->activate(true);
}

void RigidBody::addImpulse(Vector3 impulse)
{
	mBtRigidBody->activate(true);
	mBtRigidBody->applyCentralImpulse(impulse.v3ToBulletV3());
}

void RigidBody::addTorque(Vector3 torque)
{
	mBtRigidBody->applyTorqueImpulse(torque.v3ToBulletV3());
}

bool RigidBody::getTrigger()
{
	return mIsTrigger;
}

float RigidBody::getMass() {
	return mMass;
}

float RigidBody::getFriction()
{
	return mFricion;
}

float RigidBody::getRestitution()
{
	return mRestitution;
}

int RigidBody::getColShape()
{
	return mColShape;
}

int RigidBody::getMovementType()
{
	return mMvType;
}

int me::RigidBody::getMask()
{
	return mMask;
}

int me::RigidBody::getGroup()
{
	return mGroup;
}

Vector3 RigidBody::getVelocity()
{
	Vector3 velocity = Vector3(0, 0, 0);
	velocity = mBtRigidBody->getLinearVelocity();
	return velocity;
}

void me::RigidBody::activeBody()
{
	mBtRigidBody->activate(true);
	enabled = true;
}

void me::RigidBody::desactiveBody()
{
	mBtRigidBody->activate(false);
	enabled = false;
}
