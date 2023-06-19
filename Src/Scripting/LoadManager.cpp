#include "LoadManager.h"

#include "MotorEngine/MotorEngineError.h"
#include <lua.hpp>
#include <LuaBridge.h>

#ifdef _DEBUG
#include <iostream>
#endif

using namespace me;

LoadManager::LoadManager()
{
#ifdef _DEBUG
	std::cout << " > LoadManager created." << std::endl;
#endif
}

LoadManager::~LoadManager()
{
#ifdef _DEBUG
	std::cout << " >>> LoadManager deleted..." << std::endl;
#endif
}

bool LoadManager::readEntities(lua_State* L, InfoScene& entitiesMap)
{
	lua_pushnil(L);

	if (!lua_istable(L, -2)) {
		errorManager().throwMotorEngineError("Read entities error",
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

		entitiesMap[entityName];

		// Read Components
		lua_pushnil(L);
		while (lua_next(L, -2) != 0) {
			if (!lua_isstring(L, -2))
				continue;

			std::string componentName = lua_tostring(L, -2);
			for (char& c : componentName)
				c = tolower(c);

			entitiesMap[entityName][componentName];

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
						std::string value;
						if (lua_isstring(L, -1))
							value = lua_tostring(L, -1);
						else if (lua_isboolean(L, -1))
							value = std::to_string(lua_toboolean(L, -1));

						fieldValue += key + ":" + value + ",";

						entitiesMap[entityName][componentName][key] = value;
					}

					if (fieldValue.size() > 0)
						fieldValue.pop_back(); // Delete last ','
				}
				else {
					if (lua_isstring(L, -1))
						fieldValue = lua_tostring(L, -1);
					else if (lua_isboolean(L, -1))
						fieldValue = std::to_string(lua_toboolean(L, -1));

					entitiesMap[entityName][componentName][fieldName] = fieldValue;
				}

				lua_pop(L, 1);
			}

			lua_pop(L, 1);
		}

		lua_pop(L, 1);
	}

	return true;
}

bool LoadManager::loadEntities(const SceneName& sceneName, InfoScene& entitiesMap,
	std::list<std::string> awake, std::list<std::string> start)
{
	// Lua Bridge load
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	// File load
	std::string path = "Assets\\Scenes\\" + sceneName;

	if (luaL_loadfile(L, path.c_str()) || lua_pcall(L, 0, 0, 0)) {
		errorManager().throwMotorEngineError("Load entities error", lua_tostring(L, -1));
		lua_close(L);
		return false;
	}

	for (auto awakeFunc : awake) {
		lua_getglobal(L, awakeFunc.c_str());
		if (lua_isfunction(L, -1)) {
			if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
				errorManager().throwMotorEngineError("Load entities error", lua_tostring(L, -1));
				lua_close(L);
				return false;
			}
		}
	}

	awake.clear();

	// Entry Point
	lua_getglobal(L, "Entities");

	// Entities Parse
	if (!readEntities(L, entitiesMap)) {
		lua_close(L);
		return false;
	}

	for (auto startFunc : start) {
		lua_getglobal(L, startFunc.c_str());
		if (lua_isfunction(L, -1)) {
			if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
				errorManager().throwMotorEngineError("Load entities error", lua_tostring(L, -1));
				lua_close(L);
				return false;
			}
		}
	}

	start.clear();

	lua_close(L);
	return true;
}
