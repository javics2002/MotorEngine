#pragma once

#include <string>
#include <map>
#include <unordered_map>

#include "Utils/Singleton.h"

namespace me {
	class Component;
	class FactoryComponent;

	class ComponentsFactory : public Singleton<ComponentsFactory>
	{
	private:
		friend Singleton<ComponentsFactory>;
		ComponentsFactory();

		std::map<std::string, FactoryComponent*> mFactories;
	public:
		~ComponentsFactory();

		me::Component* create(const std::string& name, std::unordered_map<std::string, std::string>& params);
		void addFactoryComponent(const std::string& name, FactoryComponent* factoryComponent);
	};

	/**
	This macro defines a compact way for using the singleton InputHandler, instead of
	writing InputHandler::instance()->method() we write ih().method()
	*/
	inline ComponentsFactory& componentsFactory() {
		return *ComponentsFactory::instance();
	}
}


