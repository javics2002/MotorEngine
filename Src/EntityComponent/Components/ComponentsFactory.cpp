#include "ComponentsFactory.h"
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

me::Component* me::ComponentsFactory::create(const ComponentName& name)
{
    assert(mFactories.count(name));
    Parameters noParams;
    return mFactories[name]->create(noParams);
}

me::Component* ComponentsFactory::create(const ComponentName& name, Parameters& params)
{
    assert(mFactories.count(name));
    return mFactories[name]->create(params);
}

void me::ComponentsFactory::destroy(const ComponentName& name, Component* component)
{
    assert(mFactories.count(name));
    mFactories[name]->destroy(component);
}

void ComponentsFactory::addFactoryComponent(const ComponentName& name, FactoryComponent* factoryComponent)
{
    mFactories[name] = factoryComponent;
}
