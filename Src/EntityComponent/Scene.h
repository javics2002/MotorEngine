/**
The main function of this class is to be the wrapper
of a set of entities.
*/

#pragma once

#ifndef __EC_SCENE
#define __EC_SCENE

#include <initializer_list>
#include <vector>
#include <list>

#include "ec.h"


namespace me {

	class Entity;

	class Scene {
	public:

		/**
		Build the foundation of the Scene.
		@param String name to identify it.
		*/
		Scene(std::string name);

		/**
		This method is meant to be the definition
		of the dynamic memory that has to be safely delete.
		*/
		virtual ~Scene();

		/**
		Add a new entity to the scene.
		@param String name to identify the new entity.
		@return Reference to the created new entity.
		*/
		Entity* addEntity(std::string name);

		/**
		Get the vector list of the entities in the scene.
		@return Reference vector of entities.
		*/
		inline const std::vector<Entity*>& getEntities() {
			return mEntities;
		};

		/**
		This method is only ever called once.
		This must be called at the instantiation of the script.
		*/
		virtual void start();

		/**
		This method is meant to be the definition 
		of those updates that has to be processed
		at the begining of the game cycle.

		Almost all the logic updates.
		*/
		void update();

		/**
		This method is meant to be the definition 
		of those updates that has to be processed
		at the end of the game cycle.

		For example: render and collisions.
		*/
		void lateUpdate();

		/**
		Safely deletes all the dead entities, 
		this means the ones who are deactivate.
		*/
		void refresh();

	protected:

		std::string mName;
		std::vector<Entity*> mEntities;

	};

};

#endif