#pragma once

#ifndef __ENTITYCOMPONENT_ENTITY
#define __ENTITYCOMPONENT_ENTITY

#include "MotorEngine/MotorEngineAPI.h"
#include "MotorEngine/InfoScene.h"
#include "ComponentsFactory.h"
#include <vector>
#include <map>

namespace me {
	class Scene;
	class Component;

	/**
	An Entity is anything that exists in a scene.
	An Entity by itself doesn�t do anything - its behaviour is defined by the Components 
	it possesses, which are stored in its mComponents map.
	An Entity has a name, a reference to the scene it exists in, and can be active or not.
	*/
	class __MOTORENGINE_API Entity {
		friend Scene;

	public:
		/**
		Build the foundation of the Entity.
		@param Scene to which it belongs.
		@param String name to identify it.
		*/
		Entity(Scene* scene, const EntityName name);

		/**
		Build the foundation of the Entity.
		@param String name to identify it.
		*/
		Entity(const EntityName name);

		/**
		Delete all the components added to the entity.
		*/
		virtual ~Entity();

		
		/**
		Add a new component. If the component already exists, notify in debug mode
		@param componentName The key of the component in the map
		@param params std::unordered_map<std::string parameterName, std::string parameterValue> 
		@return Reference to the new component or nullptr if something went wrong.
		*/
		Component* addComponent(const ComponentName& componentName, Parameters& params);

		/**
		Add a new component. If the component already exists, returns a reference to the existing component.
		@tparam T component type to be returned
		@param params std::unordered_map<std::string parameterName, std::string parameterValue>
		@return Reference to the new component or nullptr if something went wrong.
		*/
		template<typename T>
		T* addComponent(const ComponentName& componentName) {
			if (hasComponent(componentName)) {
#ifdef _DEBUG
				std::cout << "Entity: " << mName << " already has the Component:" << componentName;
#endif
				return nullptr;
			}

			T* component = static_cast<T*>(componentsFactory().create(componentName));

			if (component) {
				mComponents.insert({ componentName, component });
				component->setEntity(this);
			}

			return component;
		};

		/**
		Remove completely a typed component.
		*/
		bool removeComponent(const ComponentName& componentName);
		
		/**
		Get the reference a suggested component.
		@param Component's key name in this Entity's map
		@return Reference to the component. Nullptr if it does not exist.
		*/
		template<typename T>
		inline T* getComponent(const ComponentName& componentName) {
			if (!hasComponent(componentName))
				return nullptr;

			return static_cast<T*>(mComponents.find(componentName)->second);
		};

		/**
		Check if the component has already been added.
		@param Component's key name in this Entity's map
		@return Boolean confirmation.
		*/
		bool hasComponent(const ComponentName& name);

		/**
		Check if the entity is active.
		@return Boolean confirmation.
		*/
		bool isActive() const;

		/**
		Set the entity activity to false.
		This will cause to be safely delete by the scene.
		*/
		void destroy();

		/**
		Get the entity name.
		@return String name.
		*/
		EntityName getName() const;

		/**
		Set the entity name to the new one.
		@param name New name.
		*/
		void setName(const EntityName name);

		/**
		Get the associated scene of the entity.
		@return Scene to which it belongs.
		*/
		Scene* getScene() const;

		/**
		Set the associated scene for the entity.
		@param Scene to which it belongs.
		*/
		void setScene(Scene* scene);

		void start();

		/**
		Run all the added components update method.
		@param dt Seconds that have passed since last update.
		*/
		void update(float dt);

		/**
		Run all the added components lateUpdate method.
		@param dt Seconds that have passed since last update.
		*/
		void lateUpdate(float dt);


		/**
		This function is called when the object collides with another object
		*/
		void onCollisionEnter(Entity* other);


		/**
		This function is called every frame while the object is colliding with another object
		*/
		void onCollisionStay(Entity* other);

		/**
		This function is called when the object stops colliding with another object
		*/
		void onCollisionExit(Entity* other);

	private:
		bool mActive;
		std::string mName;
		Scene* mScene;
		std::map<ComponentName, Component*> mComponents;
	};
};

#endif