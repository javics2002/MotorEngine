#include "SceneManager.h"
#include "Scene.h"


namespace me {

    SceneManager::SceneManager() :
        mActiveScene(nullptr)
    {
#ifdef _DEBUG
        std::cout << " > SceneManager created." << std::endl;
#endif
    };

    SceneManager::~SceneManager() {
        mScenes.clear();

#ifdef _DEBUG
        std::cout << " >>> SceneManager deleted..." << std::endl;
#endif
    };

    std::shared_ptr<Scene> SceneManager::addScene(const std::string& name) {
        auto scene = std::make_shared<Scene>(name);
        if (scene != nullptr) {
            mScenes.emplace(name, scene);
        };
        return scene;
    };

    void SceneManager::removeScene(const std::string& name) {
        auto it = mScenes.find(name);
        if (it != mScenes.end()) {
            mScenes.erase(it);
        };
    };

    std::shared_ptr<Scene> SceneManager::getScene(const std::string& name) const {
        auto it = mScenes.find(name);
        if (it != mScenes.end()) {
            return it->second;
        };
        return nullptr;
    };

    void SceneManager::renameScene(const std::string& oldName, const std::string& newName) {
        auto it = mScenes.find(oldName);
        auto dst = mScenes.find(newName);
        if (it != mScenes.end() && oldName != newName && dst == mScenes.end()) {
            it->second->setName(newName);
            mScenes.emplace(newName, std::move(it->second));
            mScenes.erase(it);
        };
    };

    void SceneManager::setActiveScene(const std::string& name) {
        auto it = mScenes.find(name);
        if (it != mScenes.end()) {
            mActiveScene = it->second;
        };
    };

    void SceneManager::update() {
        if (mActiveScene) {
            mActiveScene->processNewEntities();
            mActiveScene->update();
            mActiveScene->lateUpdate();
            mActiveScene->refresh();
        };
    };

};