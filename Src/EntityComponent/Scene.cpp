#include "Scene.h"

#include "Entity.h"


namespace me {

	Scene::Scene(std::string name) : 
		mName(name) //
	{
	};

	Scene::~Scene() {
		for (auto e : mEntities) {
			delete e;
		};
	};

	Entity* Scene::addEntity(std::string name) {
		Entity* e = new Entity(this, name);
		if (e != nullptr) {
			mEntities.emplace_back(e);
		};
		return e;
	};

	void Scene::start() {
#ifdef _DEBUG
		std::cout << "Scene " << mName << " started.";
#endif
	};

	void Scene::update() {
		auto n = mEntities.size();
		for (auto i = 0u; i < n; i++)
			mEntities[i]->update();
	};

	void Scene::lateUpdate() {
		auto n = mEntities.size();
		for (auto i = 0u; i < n; i++)
			mEntities[i]->lateUpdate();
	};

	void Scene::refresh() {

		// remove dead entities from the list of entities
		mEntities.erase( //
			std::remove_if( //
				mEntities.begin(), //
				mEntities.end(), //
				[](const Entity* e) { //
			if (e->isActive()) {
				return false;
			}
			else {
				delete e;
				return true;
			};
		}), //
			mEntities.end());

	};

};