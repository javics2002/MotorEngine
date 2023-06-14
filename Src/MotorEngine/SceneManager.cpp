#include "SceneManager.h"
#include "Scene.h"
#include "EntityComponent/Entity.h"
#include "Utils/MotorEngineError.h"

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

void SceneManager::update(const double& dt, bool& q) {
	if (mActiveScene) {
		mActiveScene->processNewEntities();
		mActiveScene->update(dt);
		mActiveScene->lateUpdate(dt);
		mActiveScene->refresh();
	}

	//If we're going to change the scene
	if (isChanging() && !loadScene())
		quit();

	if (mQuit)
		q = true;
}

void SceneManager::change(std::string newScene, std::list<std::string> awake, std::list<std::string>start) {
    mNewScene = newScene;
	mChange = true;

	for (auto awakeFunc : awake)
		mAwake.push_back(awakeFunc);
	for (auto startFunc : start)
		mAwake.push_back(startFunc);
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

bool SceneManager::loadEntities(const SceneName& sceneName, std::list<std::string> awake, std::list<std::string>start) {
	
	// Lua Bridge load
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	// File load
	std::string path = "Assets\\Scenes\\" + sceneName;

	if (luaL_loadfile(L, path.c_str()) || lua_pcall(L, 0, 0, 0)) {
#ifdef _DEBUG;
		throwMotorEngineError("Load entities error", lua_tostring(L, -1));
		std::cout << lua_tostring(L, -1) << "\n";
#endif
		lua_close(L);
		return false;
	}

	for (auto awakeFunc : awake) {
		lua_getglobal(L, awakeFunc.c_str());
		if (lua_isfunction(L, -1)) {
			if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
				throwMotorEngineError("Load entities error", lua_tostring(L, -1));
				lua_close(L);
				return false;
			}
		}
	}

	awake.clear();

	// Entry Point
	lua_getglobal(L, "Entities");

	// Entities Parse
	if (readEntities(L))
	{    // Entities to Scene
		if (pushEntities())
			mEntitiesMap.clear();
		else {
			lua_close(L);
			return false;
		}
	}
	else {
		lua_close(L);
		return false;
	}

	for (auto startFunc : start) {
		lua_getglobal(L, startFunc.c_str());
		if (lua_isfunction(L, -1)) {
			if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
				throwMotorEngineError("Load entities error", lua_tostring(L, -1));
				lua_close(L);
				return false;
			}
		}
	}

	start.clear();

	lua_close(L);
	return true;
}

void SceneManager::deleteAllScenes() {
	for (auto scene : mScenes)
		delete scene.second;

	mScenes.clear();
}

bool SceneManager::loadScene() {

	mChange = false;
	addScene(mNewScene);

	if (getActiveScene() != nullptr) {
		if (mNewScene == getActiveScene()->getName())
			return false;

		if (mScenes.count(getActiveScene()->getName()))
			removeScene(getActiveScene()->getName());
	}

	sceneManager().setActiveScene(mNewScene);
	return sceneManager().loadEntities(mNewScene, mAwake, mStart);
}

bool SceneManager::readEntities(lua_State* L) {
	lua_pushnil(L);

	if (!lua_istable(L, -2)) {
		throwMotorEngineError("Read entities error", 
			std::string("Expected a table of entities, got ") + std::string(lua_typename(L, lua_type(L, -2))));
		std::cout << "Expected a table of entities, got " << lua_typename(L, lua_type(L, -2)) << "\n";
		return false;
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

	return true;
}

bool SceneManager::pushEntities() {
	// Get active scene and call it
	if (!mActiveScene->pushEntities(mEntitiesMap))
		return false;

	mActiveScene->processNewEntities();

	return true;
}