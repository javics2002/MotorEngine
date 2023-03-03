#include "SceneManager.h"
#include "Scene.h"


namespace me {

    SceneManager::SceneManager() :
        mActiveScene(nullptr)
    {
    };

    SceneManager::~SceneManager() {
        mScenes.clear();
    };

    std::shared_ptr<Scene> SceneManager::addScene(const std::string& name) {
        auto scene = std::make_shared<Scene>(this, name);
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