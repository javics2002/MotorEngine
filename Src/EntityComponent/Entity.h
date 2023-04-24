/**
The main function of this class is to be the wrapper 
of a set of components.
*/

#pragma once

#ifndef __ENTITYCOMPONENT_ENTITY
#define __ENTITYCOMPONENT_ENTITY

#include "MotorEngine/MotorEngineAPI.h"
#include "InfoScene.h"
#include "Components/ComponentsFactory.h"
#include <vector>
#include <map>

namespace me {
	class Scene;
	class Component;

	/**
	An Entity is anything that exists in a scene.
	An Entity by itself doesn´t do anything - its behaviour is defined by the Components 
	it possesses, which are stored in the mComponents map.
	An Entity has a name, a reference to the scene it exists in and can be active or not.
	*/
	class __MOTORENGINE_API Entity {
		friend Scene;

	public:
		/**
		Build the foundation of the Entity.
		@param Scene to which it belongs.
		@param String name to identify it.
		*/
		Entity(Scene* scn, const SceneName name);

		/**
		Build the foundation of the Entity.
		@param String name to identify it.
		*/
		Entity(const SceneName name);

		/**
		Delete all the components added to the entity.
		*/
		virtual ~Entity();

		
		/**
		Add a new component. If the component already exists, write a cout in debug mode
		@param componentName The key of the component in the map
		@param params std::unordered_map<std::string parameterName, std::string parameterValue> 
		@return Reference to the new component.
		*/
		Component* addComponent(const ComponentName& componentName, Parameters& params);

		/**
		Add a new component. If the component already exists, returns a reference to the existing component.
		@tparam T component type to be returned
		@param params std::unordered_map<std::string parameterName, std::string parameterValue>
		@return Reference to the new component.
		*/
		template<typename T>
		T* addComponent(const ComponentName& componentName) {
			T* component = static_cast<T*>(componentsFactory().create(componentName));

			if (!hasComponent(componentName)) {
				mComponents.insert({ componentName, component });
				component->setEntity(this);
				component->start();
			}
			else
				return getComponent<T>(componentName);

			return component;
		};

		/**
		Remove completely a typed component.
		*/
		bool removeComponent(const ComponentName& componentName);
		
		/**
		Get the reference a suggested component.
		@param key name  in the map
		@return Reference to the component.
		*/
		template<typename T>
		inline T* getComponent(const ComponentName& componentName) {
			if (!hasComponent(componentName))
				return nullptr;

			return static_cast<T*>(mComponents.find(componentName)->second);
		};

		/**
		Check if the component has already been added.
		@param key name  in the map
		@return Boolean confirmation.
		*/
		inline bool hasComponent(const ComponentName& name) {
			return mComponents.find(name) != mComponents.end();
		};

		/**
		Check if the entity is active.
		@return Boolean confirmation.
		*/
		inline bool isActive() const {
			return mActive;
		};

		/**
		Set the entity activity to false.
		This will cause to be safely delete by the scene.
		*/
		inline void destroy() {
			mActive = false;
		};

		/**
		Get the entity name.
		@return String name.
		*/
		inline EntityName getName() const {
			return mName;
		};

		/**
		Set the entity name to the new one.
		@param String name.
		*/
		inline void setName(const EntityName name) {
			mName = name;
		};

		/**
		Get the associated scene of the entity.
		@return Scene to which it belongs.
		*/
		inline Scene* getScene() const {
			return mScene;
		};

		/**
		Set the associated scene for the entity.
		@param Scene to which it belongs.
		*/
		inline void setScene(Scene* scene) {
			mScene = scene;
		};

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