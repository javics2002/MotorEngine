/**
The main function of this class is to be the wrapper
of a set of entities.
*/

#pragma once

#ifndef __ENTITYCOMPONENT_SCENE
#define __ENTITYCOMPONENT_SCENE

#include "MotorEngine/MotorEngineAPI.h"
#include "InfoScene.h"
#include <memory>
#include <initializer_list>

namespace me {
	class Entity;

	/**
	A Scene is a collection of Entities that exist in the same spatial context,
	so they can aknowledge their presence and interact with each other.
	The scene calls the start and update methods of all of its Entities
	*/
	class __MOTORENGINE_API Scene {
	public:
		/**
		Build the foundation of the Scene.
		@param String name to identify it.
		*/
		Scene(const SceneName name);

		/**
		This method is meant to be the definition
		of the dynamic memory that has to be safely delete.
		*/
		virtual ~Scene();

		/**
		Prepares a new entity to be safely add to the scene.
		This assumes that the name is a unique identifier.
		@param String name to identify the new entity.
		@return Created new entity.
		*/
		std::shared_ptr<Entity> addEntity(const EntityName name);

		/**
		Prepares an entity to be safely remove from the scene.
		This assumes that the name is a unique identifier.
		@param String name to identify the entity to be remove.
		*/
		void removeEntity(const EntityName& name);

		/**
		Get a vector of all entities in the scene.
		@return Vector of Entity pointers.
		*/
		std::vector<std::shared_ptr<Entity>> getEntities() const;

		/**
		Finds and returns an entity in the scene with the given name.
		If no entity with the given name is found
		or if it's deactivated, returns nullptr.
		This assumes that the name is a unique identifier,
		it there is more than one entity with that name
		then the first found entity will be return.
		@param String name of the entity to be found.
		@return Entity with the given name, or nullptr if not found.
		*/
		std::shared_ptr<Entity> findEntity(const EntityName& name) const;

		/**
		Get the scene name.
		@return String name.
		*/
		inline const EntityName getName() const {
			return mName;
		};

		/**
		Set the scene name to the new one.
		@param String name.
		*/
		inline void setName(const SceneName name) {
			mName = name;
		};

		/**
		Rename an entity name to the new one.
		@param String oldName to be change.
		@param String newName to be set.
		*/
		void renameEntity(const EntityName& oldName, const EntityName& newName);

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
		Safely deletes dead entities from map, 
		this means the ones who are deactivate.
		Fact: std::erase_if() was added to the C++ Standard Library in C++20.
		*/
		void refresh();

		/**
		Safely adds the new entities from map,
		by deferring the addition of the new entity 
		to the mEntities map until after the loop has completed.
		*/
		void processNewEntities();

		/**
		Safely adds the new entities from unordered_map passed by the sceneManager
		@param entitiesMap is the unordered_map that contains all the information about the entity and its components.
		*/
		void pushEntities(InfoScene& entitiesMap);

	protected:
		SceneName mName;
		std::vector<std::shared_ptr<Entity>> mNewEntities;
		std::unordered_map<EntityName, std::shared_ptr<Entity>> mEntities;
	};
};

#endif