#pragma once
#ifndef __ENTITYCOMPONENT_COMPONENTSFACTORY
#define __ENTITYCOMPONENT_COMPONENTSFACTORY

#include "MotorEngine/MotorEngineAPI.h"
#include "EntityComponent/InfoScene.h"
#include "Utils/Singleton.h"

namespace me {
	class Component;
	class FactoryComponent;

	/**
	The ComponentsFactory class stores a collection of FactoryComponent that
	creates and destroys components defined at runtime.
	*/
	class __MOTORENGINE_API ComponentsFactory : public Singleton<ComponentsFactory>
	{
		friend Singleton<ComponentsFactory>;
		ComponentsFactory();

		//Pairs a component name with its factory
		std::unordered_map<ComponentName, FactoryComponent*> mFactories;

	public:
		~ComponentsFactory();

		/**
		Creates a component by default.
		@param name Name of the component to be created
		@returns Pointer to the component created
		*/
		Component* create(const ComponentName& name);

		/**
		Creates a component and configures it with the parameters especified.
		@param name Name of the component to be created
		@param params Parameters to configure the components in pairs of 
			<std::string parameterName, std::string parameterValue>
		@returns Pointer to the component created
		*/
		Component* create(const ComponentName& name, Parameters& params);

		/**
		Deletes a component
		@param name Name of the component to be deleted
		@param component Component to be deleted
		*/
		void destroy(const ComponentName& name, Component* component);

		/**
		Adds a FactoryComponent to mFactories at runtime
		@param name Name of the components the new FactoryComponent creates
		@param factoryComponent The new factoryComponent
		*/
		void addFactoryComponent(const ComponentName& name, FactoryComponent* factoryComponent);
	};

	/**
	This macro defines a compact way for using the singleton ComponentsFactory, instead of
	writing ComponentsFactory::instance()->method() we write componentsFactory().method()
	*/
	inline ComponentsFactory& componentsFactory() {
		return *ComponentsFactory::instance();
	}
}
#endif