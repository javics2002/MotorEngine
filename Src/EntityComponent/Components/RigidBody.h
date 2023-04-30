#pragma once

#ifndef __ENTITYCOMPONENT_RIGIDBODY
#define __ENTITYCOMPONENT_RIGIDBODY

#include "Component.h"
#include "Transform.h"
#include "Collider.h"
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
		//layers it can collide with, max 32 bits
		//example of a mask, mask =  5 means that the rigidbody can collides with layers 1 and 3 because 5 is 101 
		//the  layer 1 corresponds to the most significant bit
		int mMask;
		int mOriginalMask;
		//current layer of the rigidbody 
		int mGroup;

		/**
		If the rigidbody is a trigger, it will detect collisions but will not influence 
		in other entities nor itself.
		*/
		bool mIsTrigger;

		Vector3 mColliderScale;

		btRigidBody* mBtRigidBody = nullptr;
		btTransform* mBtTransform = nullptr;

		Transform* mTransform = nullptr;
		Collider* mCollider = nullptr;

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
		void setMask(int mask);
		void setGroup(int group);
		void setVelocity(Vector3 linearVelocity);
		void setAngularVelocity(Vector3 angularVelocity);

		bool getTrigger();
		float getMass();
		float getFriction();
		float getRestitution();
		int  getColShape();
		int getMovementType();
		int getMask();
		int getGroup();
		float getGravity();
		Vector3 getVelocity();
		Vector3 getAngularVelocity();


		void activeBody();
		void desactiveBody();

		/**
		Apply a force to the rigidBody

		@param force is the vector of the force to apply
		*/
		void addForce(Vector3 force);

		/**
		Apply a impulse to the rigidBody

		@param impulse is the vector of the impulse to apply
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

