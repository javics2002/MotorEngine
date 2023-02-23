#pragma once

#ifndef __ENTITYCOMPONENT_TRANSFORM
#define __ENTITYCOMPONENT_TRANSFORM

#include "Component.h"
#include <Vector3.h>
#include <list>

namespace me {

	/*
	*The Transform class represents a position, rotation, and scale in 3D space and can be attached to entities.
	*/
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		void update() override;

		Vector3<float> getPosition();
		Vector3<float> getRotation();
		Vector3<float> getScale();

		void setPosition(Vector3<float> newPosition);
		void setRotation(Vector3<float> newRotation);
		void setScale(Vector3<float> newScale);

		void translate(Vector3<float> translation);
		void rotate(Vector3<float> rotation);
		void scaleF(float scale);

		int childCount();
		void addChild(Transform* child);
		void removeChild(Transform* child);
		Transform* getChild(int index);

		Transform* getParent();

	private:

		Vector3<float> mPosition;
		Vector3<float> mRotation;
		Vector3<float> mScale;

		Vector3<float> mLocalPosition;
		Vector3<float> mLocalRotation;
		Vector3<float> mLocalScale;

		Transform* mParent;

		std::list<Transform*> mChildren;
	};
}
#endif


