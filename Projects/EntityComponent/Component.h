/**
This abstract class is meant to be the root 
for any behavior designed as a component.
*/

#pragma once
#ifndef __EC_COMPONENT
#define __EC_COMPONENT


namespace me {

	class Entity;

	class Component {
	public:

		/**
		Build the foundation of the component.
		*/
		Component();

		/**
		This method is meant to be the definition
		of the dynamic memory that has to be safely delete.
		*/
		virtual ~Component() {}

		/**
		Set the associated entity to the component.

		This method is meant to be use at the same time as start,
		because it's not recomended to switch the entity at execution.
		*/
		inline void setEntity(Entity* e);

		/**
		Get the entity associated reference.
		@return Reference to the entity.
		*/
		inline Entity* getEntity();

		/**
		This method is only ever called once.
		It is called in the instantiation of the script.
		*/
		virtual void start() {}

		/**
		This method is meant to be the definition 
		of those updates that has to be processed
		at the begining of the game cycle.

		Almost all the logic updates.
		*/
		virtual void update() {}

		/**
		This method is meant to be the definition 
		of those updates that has to be processed
		at the end of the game cycle.

		For example: render and collisions.
		*/
		virtual void lateUpdate() {}

	protected:

		Entity* entity_;

	};

};

#endif