#include "ComponentsFactory.h"

#include "Component.h"
#include "FactoryComponent.h"

#include <cassert>

using namespace me;


me::ComponentsFactory::ComponentsFactory()
{
    
}

me::ComponentsFactory::~ComponentsFactory()
{
    for (auto& f : mFactories) {
        delete f.second;
    }

    mFactories.clear();
}

me::Component* ComponentsFactory::create(const std::string & name, std::unordered_map<std::string, std::string>& params)
{
    assert(mFactories.count(name));
    return mFactories[name]->create(params);
}

void ComponentsFactory::addFactoryComponent(const std::string& name, FactoryComponent* factoryComponent)
{
    mFactories[name] = factoryComponent;
}
