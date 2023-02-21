#pragma once
#ifndef __BULLET_PHYSICS_MANAGER
#define __BULLET_PHYSICS_MANAGER

#include "Utils/Singleton.h"

#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>

namespace me {

	class PhysicsManager : public Singleton<PhysicsManager>
	{

		friend Singleton<PhysicsManager>;
		PhysicsManager();

		btDiscreteDynamicsWorld* mDynamicsWorld;
		btDispatcher* mDispatcher;
		btBroadphaseInterface* mBroadphaseInterface;
		btCollisionConfiguration* mCollisionConfiguration;

		btRigidBody* mRigidBody;

	public:

		~PhysicsManager() override;

	};

	/**
	This macro defines a compact way for using the singleton PhysicsManager, instead of
	writing InputHandler::instance()->method() we write ih().method()
	*/
	inline PhysicsManager& pm() {
		return *PhysicsManager::instance();
	}

}

#endif