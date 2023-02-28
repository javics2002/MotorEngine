#include "Entity.h"


namespace me {

	Entity::Entity(Scene* scn, std::string name) :
		active_(true), //
		name_(name), // 
		scn_(scn), //
		cmpArray_() //
	{
	};

	Entity::~Entity() {
		for (auto c : components_) {
			delete c;
		};
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
			components_[i]->update();
		};
	};

	void Entity::lateUpdate() {
		std::size_t n = components_.size();
		for (auto i = 0u; i < n; i++) {
			components_[i]->lateUpdate();
		};
	};

};