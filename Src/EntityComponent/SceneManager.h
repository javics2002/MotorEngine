#pragma once

#ifndef __ENTITYCOMPONENT_SCENE_MANAGER
#define __ENTITYCOMPONENT_SCENE_MANAGER

#include "MotorEngine/MotorEngineAPI.h"
#include "Utils/Singleton.h"
#include "InfoScene.h"
#include <memory>

class lua_State;

namespace me {
    class Scene;
    class Entity;
    /**
    SceneManager stores all existing scenes and swaps which one is the active one
    at will. All other scenes are inactive.
    */
    class __MOTORENGINE_API SceneManager : public Singleton<SceneManager> {
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
        Scene* addScene(const SceneName& name);

        /**
        Remove an scene from the SceneManager.
        This assumes that the name is a unique identifier.
        @param String name to identify the scene to be remove.
        */
        void removeScene(const SceneName& name);

        /**
        Get an scene from the SceneManager.
        This assumes that the name is a unique identifier.
        @param String name to identify the scene suggested.
        */
        Scene* getScene(const SceneName& name) const;

        /**
        Get the scene that is actually active from the SceneManager.
        */
        inline Scene* getActiveScene() const {
            return mActiveScene;
        };

        /**
        Rename an scene name to the new one.
        @param String oldName to be change.
        @param String newName to be set.
        */
        void renameScene(const SceneName& oldName, const SceneName& newName);

        /**
        Set the active scene from the SceneManager.
        This assumes that the name is a unique identifier.
        @param String name to identify the scene suggested.
        */
        void setActiveScene(const SceneName& name);

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
        int loadEntities(const SceneName& sceneName);

        void deleteAllScenes();

        int addGameManager(const SceneName& sceneName);

        Entity* getGameManager();

        void changeScene(std::string newScene);


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


        std::unordered_map<SceneName, Scene*> mScenes;
        Scene* mActiveScene;
        Entity* mGameManager = nullptr;
        InfoScene mEntitiesMap;
    };

    /**
    This macro defines a compact way for using the singleton SceneManager, 
    instead of writing SceneManager::instance()->method() we write sceneManager().method()
    */
    inline SceneManager& sceneManager() {
        return *SceneManager::instance();
    };

};

#endif