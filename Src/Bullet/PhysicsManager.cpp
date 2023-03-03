#include "PhysicsManager.h"

#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <BulletCollision/CollisionShapes/btCylinderShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>

me::PhysicsManager::PhysicsManager()
{
	mCollisionConfiguration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
	mBroadphaseInterface = new btDbvtBroadphase();

	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphaseInterface, nullptr, mCollisionConfiguration);
}

me::PhysicsManager::~PhysicsManager()
{
}

void me::PhysicsManager::addRigidBody(btRigidBody* rigidBody)
{
	mDynamicsWorld->addRigidBody(rigidBody);
}

void me::PhysicsManager::addVehicle(btActionInterface* vehicle)
{
	mDynamicsWorld->addVehicle(vehicle);
}

btCollisionShape* me::PhysicsManager::createShape(Shapes shape, btVector3* scale)
{
	
	btCollisionShape* shape_;

	switch (shape)
	{

	case SHAPES_SPHERE:
		shape_ = new btSphereShape(scale->length());
		break;
	case SHAPES_BOX:
		shape_ = new btBoxShape(*scale);
		break;
	case SHAPES_CYLINDER:
		shape_ = new btCylinderShape(*scale);
		break;
	case SHAPES_CAPSULE:
		shape_ = new btCapsuleShape(scale->x(), scale->y());
		break;
	default:
		shape_ = new btSphereShape(scale->length());
		break;
	}

	return shape_;

}

btRigidBody*me::PhysicsManager::createRigidBody(btTransform* transform, btVector3* scale, Shapes shape, MovementType mvType, bool isTrigger, float friction, float mass, float restitution)
{

	btCollisionShape* colShape;

	colShape = createShape(shape, scale);
	
	//Initially the rigidBody  is in repose
	btVector3 reposeInertia(0, 0, 0);

	//Stores the initial position and orientation of the rigid object to update them with each iteration
	btDefaultMotionState* dfMotionState = new btDefaultMotionState(*transform);

	//Info to create rigidBody
	btRigidBody::btRigidBodyConstructionInfo rbContruction = btRigidBody::btRigidBodyConstructionInfo(mass,  dfMotionState, colShape, reposeInertia);

	btRigidBody *rb = new btRigidBody(rbContruction);

	//If the object is dynamic, calculate the localInertia
	if (mvType == MOVEMENT_TYPE_DYNAMIC) {
		colShape->calculateLocalInertia(mass, reposeInertia);
	}

	rb->setRestitution(restitution);
	rb->setFriction(friction);
	rb->setCollisionFlags(mvType);

	if (isTrigger) {
		rb->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}

	return rb;

}

void me::PhysicsManager::update(const float& dt)
{
	//cout << "5";
	mDynamicsWorld->stepSimulation(dt);
}


