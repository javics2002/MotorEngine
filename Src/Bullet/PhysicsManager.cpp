#include "PhysicsManager.h"


/**
* Constructor for the PhysicsManager class. Initializes a default collision configuration,
* a collision dispatcher, a broadphase interface, and a dynamics world.
*/
me::PhysicsManager::PhysicsManager()
{
	mCollisionConfiguration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
	mBroadphaseInterface = new btDbvtBroadphase();

	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphaseInterface, nullptr, mCollisionConfiguration);
}


/**
* Destructor for the PhysicsManager class. TO DO.
*/
me::PhysicsManager::~PhysicsManager()
{
}

/**
* Adds a rigid body to the dynamics world. The rigid body will be subject to physical forces
* and will interact with other objects in the world.
*
* @param rigidBody A pointer to the btRigidBody to add to the dynamics world.
*/
void me::PhysicsManager::addRigidBody(btRigidBody* rigidBody)
{
	mDynamicsWorld->addRigidBody(rigidBody);
}

/**
* Adds a vehicle to the dynamics world. The vehicle will be subject to physical forces
* and will interact with other objects in the world.
*
* @param vehicle A pointer to the btActionInterface that represents the vehicle.
*/
void me::PhysicsManager::addVehicle(btActionInterface* vehicle)
{
	mDynamicsWorld->addVehicle(vehicle);
}

/**
* Adds a ghost object to the dynamics world. A ghost object is a collision shape that can detect
* collisions, but does not participate in the physics simulation. Ghost objects are useful for
* implementing triggers and other types of sensors.
*
* @param ghostShape A pointer to the btCollisionShape that represents the ghost object.
*/
void me::PhysicsManager::addGhostObject(btCollisionShape* ghostShape)
{
	btGhostObject* ghostObject = new btGhostObject();
	ghostObject->setCollisionShape(ghostShape);
	//We need to add btTransform and add it to the ghostObject //TO IMPLEMENT
	ghostObject->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
}
