#pragma once

#ifndef __ENTITYCOMPONENT_RIGIDBODY
#define __ENTITYCOMPONENT_RIGIDBODY

#include "Component.h"
#include "Transform.h"

class btRigidBody;
class btTransform;
class btQuaternion;
class btCollisionShape;

namespace me{

	class __MOTORENGINE_API RigidBody : public Component
	{
		int mColShape;
		int mMvType;

		float mMass;
		float mFricion;
		float mRestitution;

		bool mIsTrigger;

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
		void update() override;
		void lateUpdate() override;

		void setTrigger(bool isTrigger);
		void setMass (float mass);
		void setFriction(float friction);
		void setRestitution(float restitution);
		void setColShape(int colShape);
		void setMomeventType(int mvType);

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
		void addForce(Vector3 force, Vector3 relativePos);

		/**
		Apply a impulse to the rigidBody

		@param impulse is the vector of the impulse to apply
		@param relativePos is the local pos of the rigidBody
		*/
		void addImpulse(Vector3 impulse, Vector3 relativePos);

	};

}

#endif

