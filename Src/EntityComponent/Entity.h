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
#include <iostream>

#include "ec.h"
#include "Component.h"


namespace me {

	class Scene;

	class Entity {
		friend Scene;

	public:

		/**
		Build the foundation of the Entity.
		@param Scene to which it belongs.
		@param String name to identify it.
		*/
		Entity(Scene* scn, std::string name);

		/**
		Delete all the components added to the entity.
		*/
		virtual ~Entity();

		/**
		Add a new component. If the component
		already exists, this will replace them.
		@param Variable number of arguments of any type.
		@return Reference to the new component.
		*/
		template<typename T, typename ...Ts>
		T* addComponent(Ts &&... args);

		/**
		Remove completely a component.
		*/
		template<typename T>
		void removeComponent();

		/**
		Get the reference a suggested component.
		@return Reference to the component.
		*/
		template<typename T>
		inline T* getComponent() {
			auto id = ec::cmpIdx<T>;
			return static_cast<T*>(cmpArray_[id]);
		};

		/**
		Check if the component has already been added.
		@return Boolean confirmation.
		*/
		template<typename T>
		inline bool hasComponent() {
			auto id = ec::cmpIdx<T>;
			return cmpArray_[id] != nullptr;
		};

		/**
		Set the associated scene for the entity.
		@param Scene to which it belongs.
		*/
		inline void setScene(Scene* scn) {
			scn_ = scn;
		};

		/**
		Get the associated scene of the entity.
		@return Scene to which it belongs.
		*/
		inline Scene* getScene() {
			return scn_;
		};

		/**
		Check if the entity is active.
		@return Boolean confirmation.
		*/
		inline bool isActive() const {
			return active_;
		};

		/**
		Set the entity activity to the boolean petition.
		@param Boolean state activity.
		*/
		inline void setActive(bool state) {
			active_ = state;
		};

		/**
		Run all the added components update method.
		*/
		void update();

		/**
		Run all the added components lateUpdate method.
		*/
		void lateUpdate();

	private:

		bool active_;
		std::string name_;
		Scene* scn_;
		std::vector<Component*> components_;
		std::array<Component*, ec::maxComponent> cmpArray_;

	};

};

#endif