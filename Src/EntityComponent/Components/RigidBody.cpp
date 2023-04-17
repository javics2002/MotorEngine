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
	delete mBtTransform;
}

void me::RigidBody::start()
{
	mTransform = mEntity->getComponent<Transform>("transform");
	
	assert(mTransform && "An Entity doesn't have the transform component");

	mBtTransform = new btTransform(btQuaternion(mTransform->getRotation().getRotationInBullet()), btVector3(mTransform->getPosition().v3ToBulletV3()));

	btVector3 scale = mTransform->getScale().v3ToBulletV3();
	btVector3 colliderScale = mColliderScale.v3ToBulletV3();

	mBtRigidBody = me::physicsManager().createRigidBody(mBtTransform, scale, colliderScale, mColShape,
										mMvType, mIsTrigger, mFricion, mMass, mRestitution);

	mBtRigidBody->setUserPointer(this);
	mBtRigidBody->setGravity(btVector3(0, 0, 0));
	
}

void me::RigidBody::update()
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
		btQuaternion rot = mBtRigidBody->getWorldTransform().getRotation();
		//update transform position and rotation
		mTransform->setPosition(Vector3(pos.x(), pos.y(), pos.z()));
		mTransform->setRotation(Vector4(rot.x(), rot.y(), rot.z(), rot.w()));

		std::cout << "rbtrx: " << mTransform->getPosition().x << " rbtry: " << mTransform->getPosition().y << " rbtrz: " << mTransform->getPosition().z << '\n';
	}
}

//To implement
void me::RigidBody::lateUpdate()
{
}

void me::RigidBody::setTrigger(bool isTrigger)
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

void me::RigidBody::setMass(float mass)
{
	mMass = mass;
}

void me::RigidBody::setFriction(float friction)
{
	mFricion = friction;
	if (mBtRigidBody != nullptr) mBtRigidBody->setFriction(friction);
}

void me::RigidBody::setRestitution(float restitution)
{
	mRestitution = restitution;
	if(mBtRigidBody != nullptr) mBtRigidBody->setRestitution(restitution);
}

void me::RigidBody::setColliderScale(Vector3 colliderScale)
{
	mColliderScale = colliderScale;
}

void me::RigidBody::setColShape(Shapes colShape)
{
	mColShape = colShape;
}

void me::RigidBody::setMomeventType(MovementType mvType)
{
	if (mBtRigidBody != nullptr) {
		//keeps the previous flags and removes the old movement to add the new one
		mBtRigidBody->setCollisionFlags(mBtRigidBody->getCollisionFlags() & ~mvType);
		mBtRigidBody->setCollisionFlags(mBtRigidBody->getCollisionFlags() | mvType);
	}
	mMvType = mvType;
}

void me::RigidBody::addForce(Vector3 force)
{
	btVector3 v = force.v3ToBulletV3();
	mBtRigidBody->applyCentralForce(v);
	std::cout << "rbx: " << mBtRigidBody->getTotalForce().x() << " rby: " << mBtRigidBody->getTotalForce().y() << " rbz: " << mBtRigidBody->getTotalForce().z() << '\n';
}

void me::RigidBody::addImpulse(Vector3 impulse)
{
	mBtRigidBody->applyCentralImpulse(impulse.v3ToBulletV3());
}

void me::RigidBody::addTorque(Vector3 torque)
{
	mBtRigidBody->applyTorque(torque.v3ToBulletV3());
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
