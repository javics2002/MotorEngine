#pragma once
#ifndef __BULLET_PHYSICS_MANAGER
#define __BULLET_PHYSICS_MANAGER

#include "Utils/Singleton.h"
#include "EntityComponent/Components/Transform.h"
#include "DebugDrawer.h"

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

#include <BulletDynamics/ConstraintSolver/btConstraintSolver.h>

#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>

#include <LinearMath/btDefaultMotionState.h>

enum Shapes {
	SHAPES_SPHERE,
	SHAPES_BOX,
	SHAPES_CYLINDER,
	SHAPES_CAPSULE
};

enum MovementType {
	MOVEMENT_TYPE_DYNAMIC,
	MOVEMENT_TYPE_STATIC,
	MOVEMENT_TYPE_KINEMATIC
};

namespace me {

	class PhysicsManager: public Singleton<PhysicsManager>
	{

	private:

		friend Singleton<PhysicsManager>;

		PhysicsManager();

		btAlignedObjectArray<btCollisionShape*> collisionShapes;

		//DynamicWorld
		btDiscreteDynamicsWorld* mDynamicsWorld;

		//Variables used to inicializate the dynamicsWorld
		btDispatcher* mDispatcher;
		btBroadphaseInterface* mBroadphaseInterface;
		btCollisionConfiguration* mCollisionConfiguration;
		btSequentialImpulseConstraintSolver* mConstraintSolver;

		DebugDrawer* mDebug;

	public:

		/**
		Destructor for the PhysicsManager class. TO DO.
		*/
		~PhysicsManager();

		/**
		Initializes a default collision configuration,
		a collision dispatcher, a broadphase interface, and a dynamics world.
		*/
		void start();

		/**
		Adds a rigid body to the dynamics world. The rigid body will be subject to physical forces
		and will interact with other objects in the world.

		@param rigidBody A pointer to the btRigidBody to add to the dynamics world.
		*/
		void addRigidBody(btRigidBody* rigidBody);

		/**
		Adds a vehicle to the dynamics world. The vehicle will be subject to physical forces
		and will interact with other objects in the world.

		@param vehicle A pointer to the btActionInterface that represents the vehicle.
		*/
		void addVehicle(btActionInterface* vehicle);

		/*
		Returns the Collision Shape of the rigidbody

		@param shape indicates the shape of the rigidbody (0 = sphere, 1 = box, 2 = cylinder, 3 = capsule)
		@param scale indicates the scale of transform
		@param size indicates the size of transform
		*/
		btCollisionShape* createShape(Shapes shape, const btVector3 &scale);

		/*
		Create and add a rigidbody to the dynamic world

		@param transform is the transform of the rigidBody
		@param scale indicates the scale of transform
		@param size indicates the size of transform
		@param shape indicates the shape of the rigidbody (0 = sphere, 1 = box, 2 = cylinder, 3 = capsule)
		@param mvType the movement of the object (0 = Dynamic, 1 = Static, 2 = Kinematic)
		@param isTrigger indicates if the object is trigger or not
		@param friction friction of the objetct
		@param mass mass of the object
		@param restitution restitution of the object
		*/
		btRigidBody*createRigidBody(btTransform *transform, const btVector3 &scale, Shapes shape, MovementType mvType, bool isTrigger, float friction, float &mass, float restitution);

		void update(const float& dt);
	};

	/**
	This macro defines a compact way for using the singleton PhysicsManager, instead of
	writing InputHandler::instance()->method() we write ih().method()
	*/
	inline PhysicsManager& physicsManager() {
		return *PhysicsManager::instance();
	}

}

#endif