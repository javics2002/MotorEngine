#include "SceneManager.h"
#include "Scene.h"
#include "EntityComponent/Entity.h"
#include "MotorEngineError.h"
#include "Scripting/LoadManager.h"

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

	InfoScene entitiesMap;

	if (!loadManager().loadEntities(mNewScene, entitiesMap, mAwake, mStart)) 
		return false;

	return pushEntities(entitiesMap);
}

bool SceneManager::pushEntities(InfoScene& entitiesMap) {
	// Get active scene and call it
	if (!mActiveScene->pushEntities(entitiesMap))
		return false;

	mActiveScene->processNewEntities();

	return !mQuit;
}