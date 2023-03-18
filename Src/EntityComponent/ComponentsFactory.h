#pragma once

#include <string>
#include <map>

#include "Component.h"
#include "FactoryComponent.h"

class ComponentsFactory
{

private:

	std::map<std::string, FactoryComponent*>mFactories;

public:

	me::Component* create(const std::string& name, const std::string &params);

	void addFactoryComponent(const std::string& name, FactoryComponent* factoryComponent);
	
};

