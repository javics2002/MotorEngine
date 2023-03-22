#include "Entity.h"
#include "Components/Component.h"

#include "Components/ComponentsFactory.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace me {

	Entity::Entity(Scene* scn, const SceneName name) :
		mActive(true), //
		mName(name), // 
		mScn(scn)
	{
#ifdef _DEBUG
		std::cout << " > Entity ( " << mName << " ) created." << std::endl;
#endif
	};

	Entity::Entity(const SceneName name) :
		mActive(true),
		mName(name),
		mScn(nullptr)
	{
#ifdef _DEBUG
		std::cout << " > Entity " << mName << " created.";
#endif
	};

	Entity::~Entity() {
		for (auto &c : mComponents) {
			delete c.second;
		};
		mComponents.clear();

#ifdef _DEBUG
		std::cout << " >>> Entity ( " << mName << " ) deleted..." << std::endl;
#endif
	};

	template<typename T>
	T* Entity::addComponent(const ComponentName& componentName) {

		T* c = componentsFactory().create(componentName);

		if (!hasComponent(componentName)) {

			mComponents.insert({ componentName, c });
			c->setEntity(this);
			c->start();
		}

#ifdef _DEBUG
		else std::cout << "Entity: " << mName << " already has the Component:" << componentName;
#endif

		return c;
	};
	
	Component* Entity::addComponent(const ComponentName& componentName, Parameters& params) {
		Component* c = componentsFactory().create(componentName, params);

		if (!hasComponent(componentName)) {

			mComponents.insert({ componentName, c });
			c->setEntity(this);
			c->start();
		}

#ifdef _DEBUG
		else std::cout << "Entity: " << mName << " already has the Component:" << componentName;
#endif

		return c;
	};

	
	
	void Entity::update() {
		if (!mActive) return;
		for (auto c : mComponents) {
			if(c.second->enabled)
				c.second->update();
		};
	};

	void Entity::lateUpdate() {
		if (!mActive) return;
		for (auto c : mComponents) {
			if (c.second->enabled)
				c.second->lateUpdate();
		};
	};

	void Entity::OnCollisionEnter(Entity* other)
	{
		for (auto &c : mComponents) {
			if(c.second->enabled)
				c.second->OnCollisionEnter(other);
		}
	}
	void Entity::OnCollisionStay(Entity* other)
	{
		for (auto &c : mComponents) {
			if (c.second->enabled)
				c.second->OnCollisionStay(other);
		}
	}
	void Entity::OnCollisionExit(Entity* other)
	{
		for (auto &c : mComponents) {
			if (c.second->enabled)
				c.second->OnCollisionExit(other);
		}
	}
};