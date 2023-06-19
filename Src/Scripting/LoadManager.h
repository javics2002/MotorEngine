#pragma once
#ifndef __SCRIPTING_LOADMANAGER
#define __SCRIPTING_LOADMANAGER

#include "Utils/Singleton.h"
#include <string>
#include <list>
#include <MotorEngine/InfoScene.h>

class lua_State;

namespace me {
    /**
    Parses .lua files and fills InfoScene maps with their information
    */
	class LoadManager : public Singleton<LoadManager> {
		friend Singleton<LoadManager>;

        /**
        Build the foundation of the SceneManager.
        */
        LoadManager();

        /*
        Parse the .lua file to an unordered_map.
        @param L is the lua_State that was opened by the function loadEntities
        @returns True on Success.
        */
        bool readEntities(lua_State* L, InfoScene& entitiesMap);

    public:
        ~LoadManager();

        /**
        Parse entities from .lua file to an unordered_map that will be passed to the current Scene
        to create the entities.
        @param sceneName has to be the name of the file with .lua INCLUDED. Example: sceneName => scene.lua
        @param awake Names of methods list to execute before reading the entities
        @param start Names of methods list to execute after reading the entities
        @returns True on Success.
        */
        bool loadEntities(const SceneName& sceneName, InfoScene& entitiesMap,
            std::list<std::string> awake, std::list<std::string>start);
	};

    /**
    This macro defines a compact way for using the singleton loadManager,
    instead of writing loadManager::instance()->method() we write loadManager().method()
    */
    inline LoadManager& loadManager() {
        return *LoadManager::Instance();
    };
}

#endif