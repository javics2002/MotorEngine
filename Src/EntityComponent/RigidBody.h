#pragma once

#ifndef __RIGID_BODY
#define  __RIGID_BODY

#include "Component.h"
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

	public:

		/*
		Set the values of the new RigidBody that will be created

		@param mass mass of the RigidBody
		@param friction the magnitude friction force
		@param restitution magnitude of the rebounding ability
		@param isTrigger indicates if the body will have collisions
		*/
		RigidBody(int colShape, int mvType, float mass, float friction, float restitution, bool isTrigger);
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

		/**
		Apply a force to the rigidBody

		@param force is the vector of the force to apply
		@param relativePos is the local pos of the rigidBody
		*/
		void addForce(Vector3<float> force, Vector3<float> relativePos);

		/**
		Apply a impulse to the rigidBody

		@param impulse is the vector of the impulse to apply
		@param relativePos is the local pos of the rigidBody
		*/
		void addImpulse(Vector3<float> impulse, Vector3<float> relativePos);

		/*
		Get the mass of the rigidBody
		*/
		float getMass();

	};

}

#endif

