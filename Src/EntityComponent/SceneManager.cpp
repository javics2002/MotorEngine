#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"

#include <lua.hpp>
#include <LuaBridge.h>

#ifdef _DEBUG
#include <iostream>
#endif

using namespace me;

SceneManager::SceneManager() : mActiveScene(nullptr) {
#ifdef _DEBUG
	std::cout << " > SceneManager created." << std::endl;
#endif
};

SceneManager::~SceneManager() {
#ifdef _DEBUG
	std::cout << " >>> SceneManager deleted..." << std::endl;
#endif

	deleteAllScenes();

	mEntitiesMap.clear();

	Scene::DeleteGlobalEntities();
};

Scene* SceneManager::addScene(const SceneName& name) {
	if(!mScenes.count(name))
		mScenes[name] = new Scene(name);

	return mScenes[name];
};

bool SceneManager::removeScene(const SceneName& name) {
	if (!mScenes.count(name)) {
		std::cout << "Try to remove nullptr Scene with this name " << name << std::endl;
		return false;
	}

		Scene* scene = mScenes[name];
		delete scene;
		mScenes.erase(name);

		return true;
}

Scene* SceneManager::getScene(const SceneName& name) const {
	auto it = mScenes.find(name);
	if (it != mScenes.end()) {
		return it->second;
	}
	return nullptr;
}

Scene* SceneManager::getActiveScene() const
{
	return mActiveScene;
}

bool SceneManager::renameScene(const SceneName& oldName, const SceneName& newName) {
	auto it = mScenes.find(oldName);
	auto dst = mScenes.find(newName);
	if (it != mScenes.end() && oldName != newName && dst == mScenes.end()) {
		it->second->setName(newName);
		mScenes.emplace(newName, std::move(it->second));
		mScenes.erase(it);
		return true;
	}

	return false;
}

bool SceneManager::setActiveScene(const SceneName& name) {
	if (!mScenes.count(name)) {
#ifdef _DEBUG
		std::cout << "Try to access a nullptr Scene with this name " << name << std::endl;
#endif

		return false;
	}

	mActiveScene = mScenes[name];

	return true;
}

void SceneManager::update(const double& dt) {
	if (mActiveScene) {
		mActiveScene->processNewEntities();
		mActiveScene->update(dt);
		mActiveScene->lateUpdate(dt);
		mActiveScene->refresh();
	}
}

void SceneManager::change(std::string newScene) {
    mNewScene = newScene;
	mChange = true;
}

void me::SceneManager::quit()
{
	mQuit = true;
}

std::string me::SceneManager::getNewScene()
{
	return mNewScene;
}

bool me::SceneManager::isChanging()
{
	return mChange;
}

bool me::SceneManager::isQuiting()
{
	return mQuit;
}

int SceneManager::loadEntities(const SceneName& sceneName) {
	
	// Lua Bridge load
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	// File load
	std::string path = "Assets\\Scenes\\" + sceneName;

	if (luaL_loadfile(L, path.c_str()) || lua_pcall(L, 0, 0, 0)) {
#ifdef _DEBUG
		std::cout << lua_tostring(L, -1) << "\n";
#endif
		lua_close(L);
		return 1;
	}

	// Entry Point
	lua_getglobal(L, "Entities");

	// Entities Parse
	if (readEntities(L) == 0)
	{    // Entities to Scene
		pushEntities();
		mEntitiesMap.clear();
	}
	else {
		lua_close(L);
		return 1;
	}

	lua_close(L);
	return 0;
}

void SceneManager::deleteAllScenes() {
	for (auto scene : mScenes)
		delete scene.second;

	mScenes.clear();
}

bool SceneManager::loadScene(const SceneName& newScene, bool eraseActiveScene) {
	std::string s = newScene;
	mChange = false;
	addScene(s);

	if (getActiveScene() != nullptr) {
		if (s == getActiveScene()->getName())
			return false;

		if (eraseActiveScene && mScenes.count(getActiveScene()->getName()))
			removeScene(getActiveScene()->getName());
	}

	sceneManager().setActiveScene(s);
	return sceneManager().loadEntities(s) == 0;
}

int SceneManager::readEntities(lua_State* L) {
	lua_pushnil(L);

	if (!lua_istable(L, -2)) {
		std::cout << "Expected a table of entities, got " << lua_typename(L, lua_type(L, -2)) << "\n";
		return 1;
	}

	// Entities found
	while (lua_next(L, -2) != 0) {
		if (!lua_isstring(L, -2)) {
			lua_pop(L, 1);
			continue;
		}

		// Entities names
		std::string entityName = lua_tostring(L, -2);

		for (char& c : entityName)
			c = tolower(c);

		mEntitiesMap[entityName];

		// Read Components
		lua_pushnil(L);
		while (lua_next(L, -2) != 0) {
			if (!lua_isstring(L, -2))
				continue;

			std::string componentName = lua_tostring(L, -2);
			for (char& c : componentName)
				c = tolower(c);

			mEntitiesMap[entityName][componentName];

			// Read Component Info
			lua_pushnil(L);
			while (lua_next(L, -2) != 0) {
				if (!lua_isstring(L, -2)) {
					lua_pop(L, 1);
					continue;
				}

				std::string fieldName = lua_tostring(L, -2);
				for (char& c : fieldName)
					c = tolower(c);

				// Component Values
				std::string fieldValue;
				if (lua_istable(L, -1)) {
					for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
						std::string key = fieldName + "_" + lua_tostring(L, -2);
						std::string value = lua_tostring(L, -1);

						fieldValue += key + ":" + value + ",";

						mEntitiesMap[entityName][componentName][key] = value;
					}

					if (fieldValue.size() > 0)
						fieldValue.pop_back(); // Delete last ','
				}
				else {
					if (lua_isstring(L, -1))
						fieldValue = lua_tostring(L, -1);
					else if (lua_isboolean(L, -1))
						fieldValue = std::to_string(lua_toboolean(L, -1));

					mEntitiesMap[entityName][componentName][fieldName] = fieldValue;
				}

				lua_pop(L, 1);
			}

			lua_pop(L, 1);
		}

		lua_pop(L, 1);
	}

	return 0;
}

void SceneManager::pushEntities() {
	// Get active scene and call it
	mActiveScene->pushEntities(mEntitiesMap);

	mActiveScene->processNewEntities();
}