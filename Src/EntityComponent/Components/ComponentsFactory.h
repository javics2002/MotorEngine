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

		me::Component* create(const ComponentName& name, Parameters& params);
		void addFactoryComponent(const ComponentName& name, FactoryComponent* factoryComponent);
	};

	/**
	This macro defines a compact way for using the singleton InputHandler, instead of
	writing InputHandler::instance()->method() we write ih().method()
	*/
	inline ComponentsFactory& componentsFactory() {
		return *ComponentsFactory::instance();
	}
}
#endif