#include "Scene.h"

#include "Entity.h"
#include "Components/ComponentsFactory.h"

#ifdef _DEBUG
#include <iostream>
#endif

using namespace me;

Scene::Scene(const SceneName name) :
	mName(name)
{
#ifdef _DEBUG
	std::cout << " > Scene ( " << mName << " ) created." << std::endl;
#endif
}

Scene::~Scene() {
	mNewEntities.clear();
	mNewGlobalEntities.clear();
	mEntities.clear();

#ifdef _DEBUG
	std::cout << " >>> Scene ( " << mName << " ) deleted..." << std::endl;
#endif
}

std::shared_ptr<Entity> Scene::addEntity(const EntityName name) {
	auto e = std::make_shared<Entity>(this, name);
	if (e != nullptr) {
		mNewEntities.push_back(e);
	}
	return e;
}

bool Scene::removeEntity(const EntityName& name) {
	auto it = mEntities.find(name);
	if (it != mEntities.end()) {
		it->second->destroy();
		return true;
	}

	it = MGlobalEntities.find(name);
	if (it != MGlobalEntities.end()) {
		it->second->destroy();
		return true;
	}

	return false;
}

std::vector<std::shared_ptr<Entity>> Scene::getEntities() const {
	std::vector<std::shared_ptr<Entity>> entities;
	entities.reserve(mEntities.size());
	for (auto& kv : mEntities) {
		entities.push_back(kv.second);
	}
	for (auto& kv : MGlobalEntities) {
		entities.push_back(kv.second);
	}
	return entities;
}

std::shared_ptr<Entity> Scene::findEntity(const EntityName& name) const {
	auto it = mEntities.find(name);
	if (it != mEntities.end() && it->second->isActive()) {
		return it->second;
	}
	it = MGlobalEntities.find(name);
	if (it != MGlobalEntities.end() && it->second->isActive()) {
		return it->second;
	}
	return nullptr;
}

const EntityName Scene::getName() const
{
	return mName;
}

void Scene::setName(const SceneName name)
{
	mName = name;
}

bool Scene::renameEntity(const EntityName& oldName, const EntityName& newName) {
	auto it = mEntities.find(oldName);
	auto dst = mEntities.find(newName);
	if (it != mEntities.end() && oldName != newName && dst == mEntities.end()) {
		it->second->setName(newName);
		mEntities.emplace(newName, std::move(it->second));
		mEntities.erase(it);
		return true;
	}

	it = MGlobalEntities.find(oldName);
	dst = MGlobalEntities.find(newName);
	if (it != MGlobalEntities.end() && oldName != newName && dst == MGlobalEntities.end()) {
		it->second->setName(newName);
		MGlobalEntities.emplace(newName, std::move(it->second));
		MGlobalEntities.erase(it);
		return true;
	}

	return false;
}

void Scene::start() {
#ifdef _DEBUG
	std::cout << "Scene " << mName << " started.";
#endif
	for (const auto& kv : mEntities)
		kv.second->start();
}

void Scene::update(const double& dt) {
	for (const auto& kv : MGlobalEntities)
		kv.second->update(dt);

	for (const auto& kv : mEntities) {
		kv.second->update(dt);
	}
}

void Scene::lateUpdate(const double& dt) {
	for (const auto& kv : MGlobalEntities)
		kv.second->lateUpdate(dt);

	for (const auto& kv : mEntities)
		kv.second->lateUpdate(dt);
}

void Scene::refresh() {
	std::erase_if(mEntities, [](const auto& kv) {
		return !kv.second->isActive();
	});

	std::erase_if(MGlobalEntities, [](const auto& kv) {
		return !kv.second->isActive();
	});
}

void Scene::processNewEntities()
{
	for (auto& entityPtr : mNewGlobalEntities) {
		MGlobalEntities.emplace(entityPtr->getName(), entityPtr);
		mEntities.erase(entityPtr->getName());
	}

	mNewGlobalEntities.clear();

	for (auto& entityPtr : mNewEntities)
		mEntities.emplace(entityPtr->getName(), entityPtr);

	for (auto& entityPtr : mNewGlobalEntities)
		entityPtr->start();

	
	for (auto& entityPtr : mNewEntities)
		entityPtr->start();




	mNewEntities.clear();
}

bool Scene::pushEntities(InfoScene& entitiesMap)
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

			if (!entity->addComponent(*componentName, *componentInfo))
				return false;
		}
	}

	return true;
}

bool Scene::promoteToGlobal(Entity* entity)
{
	auto it = mEntities.find(entity->getName());
	if (it == mEntities.end())
		return false;
	mNewGlobalEntities.push_back(it->second);
	return true;
}

void Scene::DeleteGlobalEntities()
{
	MGlobalEntities.clear();
}

Scene::EntitiesMap Scene::MGlobalEntities;