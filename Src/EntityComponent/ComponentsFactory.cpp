#include "ComponentsFactory.h"

me::Component* ComponentsFactory::create(const std::string & name, const std::string& params)
{
    return mFactories[name]->create(params);
}

void ComponentsFactory::addFactoryComponent(const std::string& name, FactoryComponent* factoryComponent)
{
    mFactories[name] = factoryComponent;
}
