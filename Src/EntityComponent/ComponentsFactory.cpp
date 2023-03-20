#include "ComponentsFactory.h"

#include "Component.h"
#include "FactoryComponent.h"

using namespace me;


me::ComponentsFactory::ComponentsFactory()
{
    
}

//me::ComponentsFactory::~ComponentsFactory()
//{
//
//}

me::Component* ComponentsFactory::create(const std::string & name, const std::unordered_map<std::string, std::string>& params)
{
    return mFactories[name]->create(params);
}

void ComponentsFactory::addFactoryComponent(const std::string& name, FactoryComponent* factoryComponent)
{
    mFactories[name] = factoryComponent;
}
