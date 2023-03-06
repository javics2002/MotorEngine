#pragma once

#ifndef __RIGID_BODY
#define  __RIGID_BODY

#include "Transform.h"

class btRigidBody;
class btTransform;
class btQuaternion;
class btCollisionShape;

namespace me{

	class RigidBody : public Component
	{

	private:

		int mColShape;
		int mMvType;

		float mMass;
		float mFricion;
		float mRestitution;

		bool mIsTrigger;

		btRigidBody* mBtRigidBody = nullptr;
		btTransform* mBtTransform = nullptr;

		Transform* mTransform = nullptr;
		btVector3 scale;

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
		RigidBody(int colShape, int mvType, float mass, float friction, float restitution, bool isTrigger);
		~RigidBody();
		RigidBody() {};

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

		/*
		Get the mass of the rigidBody
		*/
		float getMass();

	};

}

#endif

