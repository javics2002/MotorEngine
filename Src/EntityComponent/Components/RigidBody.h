#pragma once

#ifndef __ENTITYCOMPONENT_RIGIDBODY
#define __ENTITYCOMPONENT_RIGIDBODY

#include "Component.h"
#include "Transform.h"
#include "Physics/PhysicsEnums.h"

class btRigidBody;
class btTransform;
class btQuaternion;
class btCollisionShape;

namespace me{
	/**
	Enables physical behaviour for the entity, based on its
	parameters: mass, friction and restitution; its shape and type.
	*/
	class __MOTORENGINE_API RigidBody : public Component
	{

		Shapes mColShape;
		MovementType mMvType;

		//Mass of the entity in kilograms
		float mMass;
		//Amount of friction with other surfaces.
		float mFricion;
		//amount of bounce of an object after a collision
		float mRestitution;

		/**
		If the rigidbody is a trigger, it will detect collisions but will not influence 
		in other entities nor itself.
		*/
		bool mIsTrigger;

		Vector3 mColliderScale;

		btRigidBody* mBtRigidBody = nullptr;
		btTransform* mBtTransform = nullptr;

		Transform* mTransform = nullptr;

	public:

		/*
		Set the values of the new RigidBody that will be created

		@param colShape indicates the shape of the rigidbody (0 = sphere, 1 = box, 2 = cylinder, 3 = capsule)
		@param mvType the movement of the object (0 = Dynamic, 1 = Static, 2 = Kinematic)
		@param mass mass of the RigidBody
		@param friction the magnitude friction force
		@param restitution magnitude of the rebounding ability
		@param isTrigger indicates if the body will have collisions
		*/
		RigidBody();
		~RigidBody();

		/*
		Starts the RigidBody of the entity for the physics
		*/
		void start() override;
		void update(const double& dt) override;
		void lateUpdate(const double& dt) override;

		void setTrigger(bool isTrigger);
		void setMass (float mass);
		void setFriction(float friction);
		void setRestitution(float restitution);
		void setColliderScale(Vector3 colliderScale);
		void setColShape(Shapes colShape);
		void setMomeventType(MovementType mvType);

		bool getTrigger();
		float getMass();
		float getFriction();
		float getRestitution();
		int  getColShape();
		int getMovementType();

		/**
		Apply a force to the rigidBody

		@param force is the vector of the force to apply
		@param relativePos is the local pos of the rigidBody
		*/
		void addForce(Vector3 force);

		/**
		Apply a impulse to the rigidBody

		@param impulse is the vector of the impulse to apply
		@param relativePos is the local pos of the rigidBody
		*/
		void addImpulse(Vector3 impulse);

		/*
		Apply  a turning force

		@param torque is the vector of the turning force
		*/
		void addTorque(Vector3 torque);
	};

}

#endif

