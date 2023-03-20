#include "Entity.h"
#include "Components/Component.h"


namespace me {

	Entity::Entity(Scene* scn, const std::string name) :
		mActive(true), //
		mName(name), // 
		mScn(scn)
	{
#ifdef _DEBUG
		std::cout << " > Entity ( " << mName << " ) created." << std::endl;
#endif
	};

	Entity::Entity(const std::string name) :
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