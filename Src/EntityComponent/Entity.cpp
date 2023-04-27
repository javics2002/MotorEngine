#include "Entity.h"
#include "Components/Component.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace me {
	Entity::Entity(Scene* scene, const SceneName name) :
		mActive(true), //
		mName(name), // 
		mScene(scene)
	{
#ifdef _DEBUG
		std::cout << " > Entity ( " << mName << " ) created." << std::endl;
#endif
	}

	Entity::Entity(const SceneName name) :
		mActive(true),
		mName(name),
		mScene(nullptr)
	{
#ifdef _DEBUG
		std::cout << " > Entity " << mName << " created.";
#endif
	}

	Entity::~Entity() {
		for (auto &c : mComponents)
			componentsFactory().destroy(c.first, c.second);

		mComponents.clear();

#ifdef _DEBUG
		std::cout << " >>> Entity ( " << mName << " ) deleted..." << std::endl;
#endif
	}
	
	Component* Entity::addComponent(const ComponentName& componentName, Parameters& params) {
		Component* c = componentsFactory().create(componentName, params);

		if (!hasComponent(componentName)) {

			mComponents.insert({ componentName, c });
			c->setEntity(this);
		}

#ifdef _DEBUG
		else std::cout << "Entity: " << mName << " already has the Component:" << componentName;
#endif

		return c;
	}

	bool Entity::removeComponent(const ComponentName& componentName)
	{
		if (hasComponent(componentName)) {
			componentsFactory().destroy(componentName, mComponents.find(componentName)->second);
			mComponents.erase(componentName);
			return true;
		}

		return false;
	}

	void Entity::start()
	{
		for (auto c : mComponents) {
			if (c.second->enabled)
				c.second->start();
		};
	}

	void Entity::update(float dt) {
		if (!mActive) return;
		for (auto c : mComponents) {
#ifdef _DEBUG
			if (c.first == "vehiclecontroller") {
				int suma = 1 + 1;
			}
#endif
			if(c.second->enabled)
				c.second->update(dt);
		};
	}

	void Entity::lateUpdate(float dt) {
		if (!mActive) return;
		for (auto c : mComponents) {
			if (c.second->enabled)
				c.second->lateUpdate(dt);
		};
	}

	void Entity::onCollisionEnter(Entity* other)
	{
		for (auto &c : mComponents) {
			if(c.second->enabled && c.first != "collider")
				c.second->onCollisionEnter(other);
		}
	}

	void Entity::onCollisionStay(Entity* other)
	{
		for (auto &c : mComponents ) {
			if (c.second->enabled  && c.first != "collider")
				c.second->onCollisionStay(other);
		}
	}

	void Entity::onCollisionExit(Entity* other)
	{
		for (auto &c : mComponents) {
			if (c.second->enabled && c.first != "collider")
				c.second->onCollisionExit(other);
		}
	}
};