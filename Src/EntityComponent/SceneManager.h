#pragma once

#ifndef __EC_SCENE_MANAGER
#define __EC_SCENE_MANAGER


#include <unordered_map>
#include <string>
#include <memory>

#include "Utils/Singleton.h"


class lua_State;

namespace me {

    class Scene;

    class SceneManager : public Singleton<SceneManager> {
        friend Singleton<SceneManager>;

    public:        

        /**
        Build the foundation of the SceneManager.
        */
        SceneManager();

        /**
        This method is meant to be the definition
        of the dynamic memory that has to be safely delete.
        */
        virtual ~SceneManager();

        /**
        Add a new Scene to the SceneManager.
        This assumes that the name is a unique identifier.
        @param String name to identify the new scene.
        */
        std::shared_ptr<Scene> addScene(const std::string& name);

        /**
        Remove an scene from the SceneManager.
        This assumes that the name is a unique identifier.
        @param String name to identify the scene to be remove.
        */
        void removeScene(const std::string& name);

        /**
        Get an scene from the SceneManager.
        This assumes that the name is a unique identifier.
        @param String name to identify the scene suggested.
        */
        std::shared_ptr<Scene> getScene(const std::string& name) const;

        /**
        Get the scene that is actually active from the SceneManager.
        */
        inline std::shared_ptr<Scene> getActiveScene() const {
            return mActiveScene;
        };

        /**
        Rename an scene name to the new one.
        @param String oldName to be change.
        @param String newName to be set.
        */
        void renameScene(const std::string& oldName, const std::string& newName);

        /**
        Set the active scene from the SceneManager.
        This assumes that the name is a unique identifier.
        @param String name to identify the scene suggested.
        */
        void setActiveScene(const std::string& name);

        /**
        Main loop of this manager, if there is an active scene 
        this will call the scene loop mehtods by the order of: 
        processNewEntities, update, lateUpdate and refresh.
        */
        void update();

        /**
        Parse entities from .lua file to an unordered_map that will be passed to the current Scene
        to create the entities.
        sceneName has to be the name of the file with .lua INCLUDED. Example: sceneName => scene.lua

        @returns Error Value, 0 if loadEntities worked correctly or 1 if
        some error appeared during this function
        */
        int loadEntities(const std::string& sceneName);

    private:

        /*
        This function parses the .lua file to the unordered_map.
        @param L is the lua_State that was opened by the function loadEntities
        @returns Error Value, 0 if loadEntities worked correctly or 1 if
        some error appeared during this function
        */
        int readEntities(lua_State* L);

        /*
        This function calls the active scene and passes the unordered_map with all the entities information
        */
        void pushEntities();

        std::unordered_map<std::string, std::shared_ptr<Scene>> mScenes;
        std::shared_ptr<Scene> mActiveScene;

        typedef std::unordered_map<std::string, std::unordered_map<std::string, std::string>> InfoEntities;
        std::unordered_map<std::string, InfoEntities> mEntitiesMap;
    };

    /**
    This macro defines a compact way for using the singleton SceneManager, 
    instead of writing SceneManager::instance()->method() we write sm().method()
    */
    inline SceneManager& sceneManager() {
        return *SceneManager::instance();
    };

};

#endif