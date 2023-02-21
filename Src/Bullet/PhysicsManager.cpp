#include "PhysicsManager.h"

me::PhysicsManager::PhysicsManager()
{
	mCollisionConfiguration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
	mBroadphaseInterface = new btDbvtBroadphase();

	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphaseInterface, nullptr, mCollisionConfiguration);

	/*mRigidBody = new btRigidBody();

	mDynamicsWorld->addRigidBody(mRigidBody);*/

}

me::PhysicsManager::~PhysicsManager()
{
}
