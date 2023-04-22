#include "Scene.h"

#include "Entity.h"
#include "Components/ComponentsFactory.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace me {

	Scene::Scene(const SceneName name) : 
		mName(name)
	{
#ifdef _DEBUG
		std::cout << " > Scene ( " << mName << " ) created." << std::endl;
#endif
	};

	Scene::~Scene() {
		mNewEntities.clear();
		mEntities.clear();

#ifdef _DEBUG
		std::cout << " >>> Scene ( " << mName << " ) deleted..." << std::endl;
#endif
	};

	std::shared_ptr<Entity> Scene::addEntity(const EntityName name) {
		auto e = std::make_shared<Entity>(this, name);
		if (e != nullptr) {
			mNewEntities.push_back(e);
		};
		return e;
	};

	void Scene::removeEntity(const EntityName& name) {
		auto it = mEntities.find(name);
		if (it != mEntities.end()) {
			it->second->destroy();
		};
	};

	std::vector<std::shared_ptr<Entity>> Scene::getEntities() const {
		std::vector<std::shared_ptr<Entity>> entities;
		entities.reserve(mEntities.size());
		for (auto& kv : mEntities) {
			entities.push_back(kv.second);
		};
		return entities;
	};

	std::shared_ptr<Entity> Scene::findEntity(const EntityName& name) const {
		auto it = mEntities.find(name);
		if (it != mEntities.end() && it->second->isActive()) {
			return it->second;
		};
		return nullptr;
	};

	void Scene::renameEntity(const EntityName& oldName, const EntityName& newName) {
		auto it = mEntities.find(oldName);
		auto dst = mEntities.find(newName);
		if (it != mEntities.end() && oldName != newName && dst == mEntities.end()) {
			it->second->setName(newName);
			mEntities.emplace(newName, std::move(it->second));
			mEntities.erase(it);
		};
	};

	void Scene::start() {
#ifdef _DEBUG
		std::cout << "Scene " << mName << " started.";
#endif
		for (const auto& kv : mEntities)
			kv.second->start();
	};

	void Scene::update() {
		for (const auto& kv : mEntities)
			kv.second->update();
	};

	void Scene::lateUpdate() {
		for (const auto& kv : mEntities)
			kv.second->lateUpdate();
	};

	void Scene::refresh() {
		std::erase_if(mEntities, [](const auto& kv) {
			return !kv.second->isActive();
		});
	};

	void Scene::processNewEntities()
	{
		for (auto& entityPtr : mNewEntities)
			mEntities.emplace(entityPtr->getName(), entityPtr);

		for (auto& entityPtr : mNewEntities)
			entityPtr->start();

		mNewEntities.clear();
	};

	void Scene::pushEntities(InfoScene& entitiesMap)
	{
		// Recorrer el mapa de entidades
		for (auto& infoEntity : entitiesMap) {
			const EntityName* entityName = &infoEntity.first;
			InfoEntity* entityComponents = &infoEntity.second;

			// Crear entidad
			auto entity = addEntity(*entityName);

			// Crear y añadir componentes
			for (auto& component : *entityComponents) {
				const ComponentName* componentName = &component.first;
				Parameters* componentInfo = &component.second;
				entity->addComponent(*componentName, *componentInfo);
			}
		}
	};
};