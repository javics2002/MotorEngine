#pragma once

#ifndef __ENTITYCOMPONENT_TRANSFORM
#define __ENTITYCOMPONENT_TRANSFORM

#include "Component.h"
#include "FactoryComponent.h"
#include "Utils/Vector3.h"
#include "Utils/Vector4.h"
#include <list>

namespace me {

	//Creates and destroys Transform components
	class FactoryTransform : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};


	/*
	*The Transform class represents a position, rotation, and scale in 3D space and can be attached to entities.
	*/
	class __MOTORENGINE_API Transform : public Component
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
		~Transform() override;

		void start() override;
		void update(const double& dt) override;

		/**
		Get the position vector of the Transform object.
		@return A Vector3 object representing the position.
		*/
		Vector3 getPosition();

		/**
		Get the linear velocity vector of the Transform object.
		@return A Vector3 object representing the linear velocity.
		*/
		Vector3 getVelocity();

		/**
		Returns the current Rotation
		*/
		Vector4 getRotation();

		/**
		Get the scale vector of the Transform object.
		@return A Vector3 object representing the scale.
		*/
		Vector3 getScale();

		/**
		Set the position vector of the Transform object.
		@param newPosition A Vector3 object representing the new position.
		*/
		void setPosition(Vector3 newPosition);

		/**
		Set the linear velocity vector of the Transform object.
		@param newPosition A Vector3 object representing the new linear velocity.
		*/
		void setVelocity(Vector3 newVelocity);

		/**
		Set the rotation vector of the Transform object.
		@param newRotation A Vector3 object representing the new rotation.
		*/
		void setRotation(Vector3 newRotation);

		/**
		Set the rotation vector of the Transform object.
		@param newRotation A Vector4 object representing the new rotation.
		*/
		void setRotation(Vector4 newRotation);

		/**
		Set the scale vector of the Transform object.
		@param newScale A Vector3 object representing the new scale.
		*/
		void setScale(Vector3 newScale);

		/**
		Translate the Transform object by a given vector.
		@param translation A Vector3 object representing the translation.
		*/
		void translate(Vector3 translation);

		/**
		Rotate the Transform object by a given vector.
		@param degrees the number of degrees to turn
		@param degrees the axis where to apply the rotation 
		*/
		void rotate(float degrees, Vector3 axis);

		/**
		Scale the Transform object by a given factor.
		@param scaleF A float representing the scale factor.
		*/
		void scaleF(float scale);


		/*
		Vector Right of the transform
		@return The vector3 value of the vector right along x axis
		*/
		Vector3 right();

		/*
		Vector Up of the transform
		@return The vector3 value of the vector up along y axis
		*/
		Vector3 up();

		/*
		Vector Forward of the transform
		@return The vector3 value of the vector forward along z axis
		*/
		Vector3 forward();

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

		/**
		Apply translation to each of the childs of a given entity.
		*/
		void childTranslation();

		/**
		Stablishes the relationship between the parent transform and the child.
		*/
		void setParent();

		/**
		Sets the name of the parent entity.
		 @param name The name of the parent.
		*/
		void setParentName(std::string name);

	private:

		Vector3 mPosition;
		Vector3 mVelocity;
		Vector3 mTranslatePosition;
		Vector4 mRotation;
		Vector3  mScale;

		Vector3 mLocalPosition;
		Vector4 mLocalRotation;
		Vector3  mLocalScale;

		Transform* mParent;
		std::string mParentName;

		std::list<Transform*> mChildren;
	};
};

#endif