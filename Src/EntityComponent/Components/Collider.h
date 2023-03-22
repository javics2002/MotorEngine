#pragma once
#ifndef __EC_COLLIDER
#define __EC_COLLIDER

#include "Component.h"

class Entity;

namespace me{


	class __MOTORENGINE_API Collider : public Component
	{
	public:
		Collider();
		virtual ~Collider();


		/**
		Set the entity activity to the boolean petition.
		@param Boolean state activity.
		*/
		void onCollisionEnter(Entity* other);

		/**
		Set the entity activity to the boolean petition.
		@param Boolean state activity.
		*/
		void onCollisionStay(Entity* other);


		/**
		Set the entity activity to the boolean petition.
		@param Boolean state activity.
		*/
		void onCollisionExit(Entity* other);

	};
}

#endif 


