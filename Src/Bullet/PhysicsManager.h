#pragma once
#ifndef __BULLET_PHYSICS_MANAGER
#define __BULLET_PHYSICS_MANAGER

#include "Utils/Singleton.h"


/*
This class represents the physics world and handles the simulation of rigid bodies.
It is responsible for collision detection and response, 
as well as integrating forces and updating the positions and orientations of bodies.
*/
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

/*
This class represents a rigid body in the simulation. It has properties like mass,
velocity, and position, and can have forces and torques applied to it.
*/
#include <BulletDynamics/Dynamics/btRigidBody.h>

/*
* It is responsible for creating collision algorithms and managing memory for collision detection. 
This configuration class sets up a dispatcher to handle collisions between pairs of objects, 
and it can be used with any kind of rigid bodies or soft bodies
*/
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>

/*
* This class is used for broadphase collision detection,
which is a way to quickly discard pairs of bodies that are not close enough to collide. 
There are several implementations available, like a simple axis-aligned bounding box (AABB) 
algorithm or a more advanced sweep-and-prune (SAP) algorithm.
*/
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>

/*
* Defines an interface for objects that can be integrated into the physics simulation as action. 
*/
#include <BulletDynamics/Dynamics/btActionInterface.h>

/*
* Is a btCollisionObject that has a collision shape but does not have a mass or physical properties. 
It is useful for representing objects that should interact with other rigid bodies 
but do not themselves move or have physics responses.
*/
#include <BulletCollision/CollisionDispatch/btGhostObject.h>


#include <BulletCollision/CollisionShapes/btCollisionShape.h>

namespace me {

	class PhysicsManager : public Singleton<PhysicsManager>
	{

		friend Singleton<PhysicsManager>;
		PhysicsManager();

		//DynamicWorld
		btDiscreteDynamicsWorld* mDynamicsWorld;

		//Variables used to inicializate the dynamicsWorld
		btDispatcher* mDispatcher;
		btBroadphaseInterface* mBroadphaseInterface;
		btCollisionConfiguration* mCollisionConfiguration;

	public:

		~PhysicsManager() override;

		void addRigidBody(btRigidBody* rigidBody);
		void addVehicle(btActionInterface* vehicle);
		void addGhostObject(btCollisionShape* ghostShape);

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