#pragma once
#ifndef __ENTITYCOMPONENT_COMPONENTSFACTORY
#define __ENTITYCOMPONENT_COMPONENTSFACTORY

#include "MotorEngine/MotorEngineAPI.h"
#include "EntityComponent/InfoScene.h"
#include "Utils/Singleton.h"

namespace me {
	class Component;
	class FactoryComponent;

	class __MOTORENGINE_API ComponentsFactory : public Singleton<ComponentsFactory>
	{
		friend Singleton<ComponentsFactory>;
		ComponentsFactory();

		std::unordered_map<ComponentName, FactoryComponent*> mFactories;

	public:
		~ComponentsFactory();

		Component* create(const ComponentName& name);
		Component* create(const ComponentName& name, Parameters& params);
		void destroy(const ComponentName& name, Component* component);
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