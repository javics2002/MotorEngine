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
    for (auto& f : mFactories)
        delete f.second;

    mFactories.clear();
}

me::Component* ComponentsFactory::create(const ComponentName& name, Parameters& params)
{
    assert(mFactories.count(name));
    return mFactories[name]->create(params);
}

void ComponentsFactory::addFactoryComponent(const ComponentName& name, FactoryComponent* factoryComponent)
{
    mFactories[name] = factoryComponent;
}
