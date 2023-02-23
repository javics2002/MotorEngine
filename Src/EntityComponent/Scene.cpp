#include "Scene.h"

namespace me {

	Scene::Scene() {
	};

	Scene::~Scene() {
		for (auto e : entities_) {
			delete e;
		}
	};

	Entity* Scene::addEntity() {
		Entity* e = new Entity(this);
		if (e != nullptr) {
			entities_.emplace_back(e);
		}
		return e;
	};

	inline const std::vector<Entity*>& Scene::getEntities() {
		return entities_;
	};

	void Scene::update() {
		auto n = entities_.size();
		for (auto i = 0u; i < n; i++)
			entities_[i]->update();
	};

	void Scene::lateUpdate() {
		auto n = entities_.size();
		for (auto i = 0u; i < n; i++)
			entities_[i]->lateUpdate();
	};

	void Scene::refresh() {

		// remove dead entities from the list of entities
		entities_.erase( //
			std::remove_if( //
				entities_.begin(), //
				entities_.end(), //
				[](const Entity* e) { //
			if (e->isActive()) {
				return false;
			}
			else {
				delete e;
				return true;
			}
		}), //
			entities_.end());

	};

};