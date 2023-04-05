#pragma once
#ifndef __EC_COLLIDER
#define __EC_COLLIDER

#include "Component.h"

class Entity;

namespace me{
	/**
	Enables the entity's onCollisionEnter, onCollisionStay and onCollisionExit callbacks
	*/
	class __MOTORENGINE_API Collider : public Component
	{
	public:
		Collider();
		virtual ~Collider();

		/**
		Executed when a collision starts.
		@param other Entity that collides with this entity.
		*/
		void onCollisionEnter(Entity* other);

		/**
		Executed when a collision starts and every frame it lasts.
		@param other Entity that collides with this entity.
		*/
		void onCollisionStay(Entity* other);


		/**
		Executed when a collision ends.
		@param other Entity that collides with this entity.
		*/
		void onCollisionExit(Entity* other);

	};
}

#endif 


