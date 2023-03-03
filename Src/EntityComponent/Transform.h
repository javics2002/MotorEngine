#pragma once

#ifndef __ENTITYCOMPONENT_TRANSFORM
#define __ENTITYCOMPONENT_TRANSFORM

#include "Component.h"
#include "Utils/Vector3.h"

#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <list>
#include <LinearMath/btQuaternion.h>


namespace me {

	/*
	*The Transform class represents a position, rotation, and scale in 3D space and can be attached to entities.
	*/
	class Transform : public Component
	{
	public:

		/**
		Construct a new Transform object with default position (0, 0, 0),
		rotation (0, 0, 0) and scale (1, 1, 1).
		*/
		Transform();

		/**
		Destroy the Transform object and its components.
		*/
		~Transform();

		void update() override;

		/**
		Get the position vector of the Transform object.

		@return A Vector3 object representing the position.
		*/
		Vector3<float> getPosition();

		/**
		Returns the current Rotation
		*/
		Ogre::Quaternion getRotation();

		/**
		Returns the current Rotation in btQuaternion
		*/
		btQuaternion  getRotationInBullet();

		/**
		Get the scale vector of the Transform object.

		@return A Vector3 object representing the scale.
		*/
		Vector3<float> getScale();

		/**
		Set the position vector of the Transform object.

		@param newPosition A Vector3 object representing the new position.
		*/
		void setPosition(Vector3<float> newPosition);

		/**
		Set the rotation vector of the Transform object.

		@param newRotation A Vector3 object representing the new rotation.
		*/
		void setRotation(Ogre::Quaternion newRotation);

		/**
		Set the scale vector of the Transform object.

		@param newScale A Vector3 object representing the new scale.
		*/
		void setScale(Vector3<float> newScale);


		/**
		Translate the Transform object by a given vector.

		@param translation A Vector3 object representing the translation.
		*/
		void translate(Vector3<float> translation);

		/**
		Rotate the Transform object by a given vector.

		@param rotation A Vector3 object representing the rotation.
		*/
		void rotate(Vector3<float> rotation);


		/**
		Scale the Transform object by a given factor.

		@param scaleF A float representing the scale factor.
		*/
		void scaleF(float scale);

		/**
		Get the number of child Transform objects.
		*/
		int childCount();

		/**
		 Add a child Transform object to the Transform object.

		 @param child A pointer to the child Transform object.
		*/
		void addChild(Transform* child);

		/**
		Remove a child Transform object from the Transform object.

		@param child A pointer to the child Transform object.
		*/
		void removeChild(Transform* child);

		/**
		Returns the child transform at the specified index.
		Returns nullptr if the index is out of range or if there are no children.

		@param index The index of the child transform to retrieve.
		 */
		Transform* getChild(int index);


		/**
		Returns the parent transform of this transform.

		@return A pointer to the parent transform of this transform.
		 */
		Transform* getParent();

	private:

		Vector3<float> mPosition;
		Ogre::Quaternion mRotation;
		Vector3<float> mScale;

		Vector3<float> mLocalPosition;
		Ogre::Quaternion mLocalRotation;
		Vector3<float> mLocalScale;

		Transform* mParent;

		std::list<Transform*> mChildren;
	};
};

#endif