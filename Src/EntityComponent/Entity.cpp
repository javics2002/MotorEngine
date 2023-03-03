#include "Entity.h"

#include "Component.h"


namespace me {

	Entity::Entity(Scene* scn, const std::string name) :
		mActive(true), //
		mName(name), // 
		mScn(scn), //
		mCmpArray() //
	{
	};

	Entity::Entity(const std::string name) :
		mActive(true),
		mName(name),
		mScn(nullptr),
		mCmpArray()
	{
	};

	Entity::~Entity() {
		for (auto c : mComponents) {
			delete c;
		};
		mComponents.clear();
	};

	template<typename T, typename ...Ts>
	T* Entity::addComponent(Ts &&... args) {
		T* c = new T(std::forward<Ts>(args)...);
		c->setEntity(this);
		c->start();
		constexpr auto id = cmpIdx<T>;

		if (mCmpArray[id] != nullptr) {
			removeComponent<T>();
		};

		mCmpArray[id] = c;
		mComponents.emplace_back(c);

		return c;
	};

	template<typename T>
	void Entity::removeComponent() {
		auto id = cmpIdx<T>;
		if (mCmpArray[id] != nullptr) {
			Component* old_cmp = mCmpArray[id];
			mCmpArray[id] = nullptr;
			mComponents.erase( //
				std::find_if( //
					mComponents.begin(), //
					mComponents.end(), //
					[old_cmp](const Component* c) { //
				return c == old_cmp;
			}));
			delete old_cmp;
		};
	}
	template<typename T>
	inline T* Entity::getComponent() {
		auto id = cmpIdx<T>;
		return static_cast<T*>(mCmpArray[id]);
	};

	template<typename T>
	inline bool Entity::hasComponent() {
		auto id = cmpIdx<T>;
		return mCmpArray[id] != nullptr;
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