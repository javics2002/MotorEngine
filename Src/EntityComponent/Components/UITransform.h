#pragma once

#ifndef __ENTITYCOMPONENT_UITRANSFORM
#define __ENTITYCOMPONENT_UITRANSFORM

#include "Component.h"
#include "Utils/Vector2.h"
#include <list>

namespace me {
	/*
	*The UITransform class represents a position, rotation, and scale in 2D space as a screen overlay and can be attached to entities.
	*/
	class __MOTORENGINE_API UITransform : public Component
	{
	public:

		/**
		Construct a new UITransform object with default position (0, 0),
		rotation (0) and scale (1, 1).
		*/
		UITransform();

		/**
		Destroy the UITransform object and its components.
		*/
		~UITransform() override;

		/**
		Get the position vector of the UITransform object.

		@return A Vector2 object representing the position.
		*/
		Vector2 getPosition();

		/**
		Returns the current Rotation
		*/
		float getRotation();

		/**
		Get the scale vector of the UITransform object.

		@return A Vector2 object representing the scale.
		*/
		Vector2 getScale();

		/**
		Set the position vector of the UITransform object.

		@param newPosition A Vector2 object representing the new position.
		*/
		void setPosition(Vector2 newPosition);

		/**
		Set the rotation of the UITransform object.

		@param newRotation A float representing the new rotation in degrees.
		*/
		void setRotation(float newRotation);

		/**
		Set the scale vector of the UITransform object.

		@param newScale A Vector2 object representing the new scale.
		*/
		void setScale(Vector2 newScale);


		/**
		Translate the UITransform object by a given vector.

		@param translation A Vector2 object representing the translation.
		*/
		void translate(Vector2 translation);

		/**
		Rotate the UITransform object by a given value in degrees.

		@param degrees Number of degrees to turn
		*/
		void rotate(float degrees);


		/**
		Scale the UITransform object by a given factor.

		@param scale A float representing the scale factor.
		*/
		void scaleF(float scale);

		/**
		Get the number of child UITransform objects.
		*/
		int childCount();

		/**
		 Add a child UITransform object to the UITransform object.

		 @param child A pointer to the child UITransform object.
		*/
		void addChild(UITransform* child);

		/**
		Remove a child UITransform object from the UITransform object.

		@param child A pointer to the child UITransform object.
		*/
		void removeChild(UITransform* child);

		/**
		Returns the child UITransform at the specified index.
		Returns nullptr if the index is out of range or if there are no children.

		@param index The index of the child UITransform to retrieve.
		 */
		UITransform* getChild(int index);


		/**
		Returns the parent UITransform of this UITransform.

		@return A pointer to the parent UITransform of this UITransform.
		 */
		UITransform* getParent();

	private:

		Vector2 mPosition;
		float mRotation;
		Vector2  mScale;

		Vector2 mLocalPosition;
		float mLocalRotation;
		Vector2  mLocalScale;

		UITransform* mParent;

		std::list<UITransform*> mChildren;
	};
};

#endif