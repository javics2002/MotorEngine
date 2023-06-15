#include "RigidBody.h"

#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "Physics/PhysicsManager.h"
#include "EntityComponent/Entity.h"
#include "MotorEngine/MotorEngineError.h"
#include "EntityComponent/Transform.h"
#include "MotorEngine/SceneManager.h"

#include <cassert>

using namespace me;

me::Component* me::FactoryRigidBody::create(Parameters& params)
{
	RigidBody* rigidbody = new RigidBody();

	rigidbody->setMass(Value(params, "mass", 0.0f));
	rigidbody->setRestitution(Value(params, "restitution", 0.0f));
	rigidbody->setFriction(Value(params, "friction", 0.0f));
	rigidbody->setTrigger(Value(params, "istrigger", false));
	rigidbody->setColShape(Shapes(Value(params, "colshape", SHAPES_BOX)));
	rigidbody->setColliderScale(Vector3(Value(params, "colliderscale_x", 1.0f),
		Value(params, "colliderscale_y", 1.0f), Value(params, "colliderscale_z", 1.0f)));
	rigidbody->setMomeventType(MovementType(Value(params, "mvtype", MOVEMENT_TYPE_STATIC)));
	rigidbody->setMask(Value(params, "mask", 15));
	rigidbody->setGroup(Value(params, "group", 1));

	return rigidbody;
}

void me::FactoryRigidBody::destroy(Component* component)
{
	delete component;
}

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
	
	if (!mTransform) {
		errorManager().throwMotorEngineError("Rigidbody Error", "An Entity doesn't have the Transform  component");
		sceneManager().quit();
	}

	mBtTransform = new btTransform(btQuaternion(mTransform->getRotation().getRotationInBullet()), btVector3(mTransform->getPosition().v3ToBulletV3()));

	btVector3 scale = mTransform->getScale().v3ToBulletV3();
	btVector3 colliderScale = mColliderScale.v3ToBulletV3();

	mBtRigidBody = me::physicsManager().createRigidBody(mBtTransform, scale, colliderScale,  mGroup, mMask, mColShape,
										mMvType, mIsTrigger, mFricion, mMass, mRestitution);

	mCollider = mEntity->getComponent<Collider>("collider");
	mOriginalMask = mMask;

	if (!mCollider) {
		errorManager().throwMotorEngineError("Rigidbody Error", "An Entity doesn't have the Collider  component");
		sceneManager().quit();
	}

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

void me::RigidBody::setVelocity(Vector3 linearVelocity)
{
	mBtRigidBody->activate(true);
	btVector3 v = btVector3(linearVelocity.x, linearVelocity.y, linearVelocity.z);
	mBtRigidBody->setLinearVelocity(v);
}

void me::RigidBody::setAngularVelocity(Vector3 angularVelocity)
{
	mBtRigidBody->activate(true);
	btVector3 w = btVector3(angularVelocity.x, angularVelocity.y, angularVelocity.z);
	mBtRigidBody->setAngularVelocity(w);
}

void me::RigidBody::addForce(Vector3 force)
{
	mBtRigidBody->activate(true);
	btVector3 v = force.v3ToBulletV3();
	mBtRigidBody->applyCentralForce(v);
}

void RigidBody::addImpulse(Vector3 impulse)
{
	mBtRigidBody->activate(true);
	mBtRigidBody->applyCentralImpulse(impulse.v3ToBulletV3());
}

void RigidBody::addTorque(Vector3 torque)
{
	mBtRigidBody->activate(true);
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

void me::RigidBody::setGravity(Vector3 newGravity)
{
	mBtRigidBody->setGravity(newGravity.v3ToBulletV3());
}

float me::RigidBody::getGravity()
{
	btVector3 vGravity = mBtRigidBody->getGravity();
	return Vector3(vGravity.getX(), vGravity.getY(), vGravity.getZ()).magnitude();
}

Vector3 RigidBody::getVelocity()
{
	Vector3 velocity = Vector3(0, 0, 0);
	velocity = mBtRigidBody->getLinearVelocity();
	return velocity;
}

Vector3 me::RigidBody::getAngularVelocity()
{
	Vector3 angularVelocity = Vector3(0, 0, 0);
	angularVelocity = mBtRigidBody->getAngularVelocity();
	return angularVelocity;
}

void me::RigidBody::activeBody()
{
	mBtRigidBody->activate(true);
	setMask(mOriginalMask);
	enabled = true;
}

void me::RigidBody::desactiveBody()
{
	mBtRigidBody->activate(false);
	setMask(0);
	enabled = false;
}

void me::RigidBody::setLinearFactor(Vector3 linearFactor)
{
	mBtRigidBody->setLinearFactor(linearFactor.v3ToBulletV3());
}

void me::RigidBody::setAngularFactor(Vector3 angularFactor)
{
	mBtRigidBody->setAngularFactor(angularFactor.v3ToBulletV3());
}