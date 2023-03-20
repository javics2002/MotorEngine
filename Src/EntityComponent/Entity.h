/**
The main function of this class is to be the wrapper 
of a set of components.
*/

#pragma once

#ifndef __EC_ENTITY
#define __EC_ENTITY

#include <algorithm>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>

#include "ec.h"


namespace me {

	class Scene;
	class Component;

	class Entity {
		friend Scene;

	public:

		/**
		Build the foundation of the Entity.
		@param Scene to which it belongs.
		@param String name to identify it.
		*/
		Entity(Scene* scn, const std::string name);

		/**
		Build the foundation of the Entity.
		@param String name to identify it.
		*/
		Entity(const std::string name);

		/**
		Delete all the components added to the entity.
		*/
		virtual ~Entity();

		
		/**
		Add a new component. If the component
		already exists, write a cout in debug mode
		@param component the key  of the component in the map
		@param Variable number of arguments of any type.
		@return Reference to the new component.
		*/
		Component* addComponent(const std::string& componentName, std::unordered_map<std::string, std::string>& params);

		template<typename T>
		T* addComponent(const std::string& componentName);

		/**
		Remove completely a typed component.
		*/
		template<typename T>
		bool removeComponent(std::string component) {
			if (hasComponent(component)) {
				delete mComponents.find(component)->second;
				mComponents.erase(component);
				return true;
			}
			return false;
		}
		

		/**
		Get the reference a suggested component.
		@param key name  in the map
		@return Reference to the component.
		*/
		template<typename T>
		inline T* getComponent(std::string component) {

			if (!hasComponent(component)) return nullptr;

			return static_cast<T*>(mComponents.find(component)->second);
		};

		/**
		Check if the component has already been added.
		@param key name  in the map
		@return Boolean confirmation.
		*/
		inline bool hasComponent(std::string component) {
			return mComponents.find(component) != mComponents.end();
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
		inline const std::string getName() const {
			return mName;
		};

		/**
		Set the entity name to the new one.
		@param String name.
		*/
		inline void setName(const std::string name) {
			mName = name;
		};

		/**
		Get the associated scene of the entity.
		@return Scene to which it belongs.
		*/
		inline Scene* getScene() const {
			return mScn;
		};

		/**
		Set the associated scene for the entity.
		@param Scene to which it belongs.
		*/
		inline void setScene(Scene* scn) {
			mScn = scn;
		};

		/**
		Run all the added components update method.
		*/
		void update();

		/**
		Run all the added components lateUpdate method.
		*/
		void lateUpdate();


		/**
		This function is called when the object collides with another object
		*/
		void OnCollisionEnter(Entity* other);


		/**
		This function is called every frame while the object is colliding with another object
		*/
		void OnCollisionStay(Entity* other);

		/**
		This function is called when the object stops colliding with another object
		*/
		void OnCollisionExit(Entity* other);

	private:

		bool mActive;
		std::string mName;
		Scene* mScn;
		std::map<std::string, Component*> mComponents;

	};

};

#endif