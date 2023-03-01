#include "Entity.h"


namespace me {

	Entity::Entity(Scene* scn, std::string name) :
		active_(true), //
		name_(name), // 
		scn_(scn), //
		cmpArray_() //
	{
	};

	Entity::Entity(std::string name):
		active_(false),
		name_(name),
		scn_(nullptr),
		cmpArray_()
	{
	}

	Entity::~Entity() {
		for (auto c : components_) {
			delete c;
		};
		components_.clear();
	};

	template<typename T, typename ...Ts>
	T* Entity::addComponent(Ts &&... args) {
		T* c = new T(std::forward<Ts>(args)...);
		c->setEntity(this);
		c->start();
		constexpr auto id = ec::cmpIdx<T>;

		if (cmpArray_[id] != nullptr) {
			removeComponent<T>();
		};

		cmpArray_[id] = c;
		components_.emplace_back(c);

		return c;
	};

	template<typename T>
	void Entity::removeComponent() {
		auto id = ec::cmpIdx<T>;
		if (cmpArray_[id] != nullptr) {
			Component* old_cmp = cmpArray_[id];
			cmpArray_[id] = nullptr;
			components_.erase( //
				std::find_if( //
					components_.begin(), //
					components_.end(), //
					[old_cmp](const Component* c) { //
				return c == old_cmp;
			}));
			delete old_cmp;
		};
	};

	void Entity::update() {
		std::size_t n = components_.size();
		for (auto i = 0u; i < n; i++) {
			if(components_[i]->enabled)
				components_[i]->update();
		};
	};

	void Entity::lateUpdate() {
		std::size_t n = components_.size();
		for (auto i = 0u; i < n; i++) {
			if (components_[i]->enabled)
				components_[i]->lateUpdate();
		};
	};

	void Entity::OnCollisionEnter(Entity* other)
	{
		for (Component* comp : components_) {
			if(comp->enabled)
				comp->OnCollisionEnter(other);
		}
	}
	void Entity::OnCollisionStay(Entity* other)
	{
		for (Component* comp : components_) {
			if (comp->enabled)
				comp->OnCollisionStay(other);
		}
	}
	void Entity::OnCollisionExit(Entity* other)
	{
		for (Component* comp : components_) {
			if (comp->enabled)
				comp->OnCollisionExit(other);
		}
	}

};