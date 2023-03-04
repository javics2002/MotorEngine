#include "Entity.h"
#include "Component.h"


namespace me {

	Entity::Entity(Scene* scn, const std::string name) :
		mActive(true), //
		mName(name), // 
		mScn(scn), //
		mCmpArray() //
	{
#ifdef _DEBUG
		std::cout << " > Entity ( " << mName << " ) created." << std::endl;
#endif
	};

	Entity::Entity(const std::string name) :
		mActive(true),
		mName(name),
		mScn(nullptr),
		mCmpArray()
	{
#ifdef _DEBUG
		std::cout << " > Entity " << mName << " created.";
#endif
	};

	Entity::~Entity() {
		for (auto c : mComponents) {
			delete c;
		};
		mComponents.clear();

#ifdef _DEBUG
		std::cout << " >>> Entity ( " << mName << " ) deleted..." << std::endl;
#endif
	};

	
	void Entity::update() {
		if (!mActive) return;

		std::size_t n = mComponents.size();
		for (auto i = 0u; i < n; i++) {
			if(mComponents[i]->enabled)
				mComponents[i]->update();
		};
	};

	void Entity::lateUpdate() {
		if (!mActive) return;

		std::size_t n = mComponents.size();
		for (auto i = 0u; i < n; i++) {
			if (mComponents[i]->enabled)
				mComponents[i]->lateUpdate();
		};
	};

	void Entity::OnCollisionEnter(Entity* other)
	{
		for (Component* comp : mComponents) {
			if(comp->enabled)
				comp->OnCollisionEnter(other);
		}
	}
	void Entity::OnCollisionStay(Entity* other)
	{
		for (Component* comp : mComponents) {
			if (comp->enabled)
				comp->OnCollisionStay(other);
		}
	}
	void Entity::OnCollisionExit(Entity* other)
	{
		for (Component* comp : mComponents) {
			if (comp->enabled)
				comp->OnCollisionExit(other);
		}
	}

};