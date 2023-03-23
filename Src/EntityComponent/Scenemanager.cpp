#include "SceneManager.h"
#include "Scene.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#ifdef _DEBUG
#include <iostream>
#include <Windows.h>
#endif

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

    int SceneManager::loadEntities(const std::string& sceneName) {
        // Cargamos Lua Bridge
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);

        // Abrimos el fichero

        //std::string path = "Assets\\Scenes\\example.lua";
        std::string path = "Assets\\Scenes\\" + sceneName;

        if (luaL_loadfile(L, path.c_str()) || lua_pcall(L, 0, 0, 0)) {
#ifdef _DEBUG
            char buffer[MAX_PATH];
            GetCurrentDirectoryA(MAX_PATH, buffer);
            std::string currentPath(buffer);

            currentPath += "\\" + path;

            //std::cout << "La ubicación del archivo es: " << currentPath << std::endl;

            std::cout << "No se encontro el archivo " << currentPath << "\n";
#endif
            return 1;
        }

        // Comenzamos en el punto de partida
        lua_getglobal(L, "Entities");

        // Parseamos las entidades
        if (readEntities(L) == 0)
            // Las mandamos a la escena
            pushEntities();
        else
            return 1;

        return 0;
    };

    int SceneManager::readEntities(lua_State* L) {
	    lua_pushnil(L);

	    if (!lua_istable(L, -2)) {
		    std::cout << "Expected a table of entities, got " << lua_typename(L, lua_type(L, -2)) << "\n";
		    return 1;
	    }
	    else {
		    // Hemos encontrado las entidades
		    while (lua_next(L, -2) != 0) {
			    if (lua_isstring(L, -2)) {
				    // Nombre de las entidades
				    std::string entityName = lua_tostring(L, -2);
				
				    for (char& c : entityName)
					    c = tolower(c);

				    mEntitiesMap[entityName];

				    // Lectura de componentes
				    lua_pushnil(L);
				    while (lua_next(L, -2) != 0) {
					    if (lua_isstring(L, -2)) {
						    std::string componentName = lua_tostring(L, -2);
						    for (char& c : componentName)
							    c = tolower(c);

                            mEntitiesMap[entityName][componentName];

						    // Lectura de información del componente
						    lua_pushnil(L);
						    while (lua_next(L, -2) != 0) {
							    if (lua_isstring(L, -2)) {
								    std::string fieldName = lua_tostring(L, -2);
								    for (char& c : fieldName)
									    c = tolower(c);

								    // Valores del componente
								    std::string fieldValue;
								    if (lua_istable(L, -1)) {
									    for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
										    std::string key = fieldName + "_" + lua_tostring(L, -2);
										    std::string value = lua_tostring(L, -1);

										    fieldValue += key + ":" + value + ",";

                                            mEntitiesMap[entityName][componentName][key] = value;
									    }

									    if(fieldValue.size() > 0)
										    fieldValue.pop_back(); // Eliminamos la ultima coma
								    }
								    else {
									    if (lua_isstring(L, -1))
										    fieldValue = lua_tostring(L, -1);
									    else if (lua_isboolean(L, -1))
										    fieldValue = std::to_string(lua_toboolean(L, -1));

                                        mEntitiesMap[entityName][componentName][fieldName] = fieldValue;
								    }
							    }
							    lua_pop(L, 1);
						    }
					    lua_pop(L, 1);
					    }
				    }
			    }
			    lua_pop(L, 1);
		    }
	    }

        return 0;
    };

    void SceneManager::pushEntities() {
        // Get active scene and call it
        mActiveScene->pushEntities(mEntitiesMap);
    };

};