#pragma once
#ifndef __MOTORENGINE_MOTORENGINE
#define __MOTORENGINE_MOTORENGINE

#include "MotorEngineAPI.h"
#include <Windows.h>
#include <chrono>
#include <string>

union SDL_Event;
class Time;

namespace me {
	/*
	class MotorEngine provides/has information about the characteristics of the Engine,
	as the initialization, main loop and memory management of the program.
	*/
	class __MOTORENGINE_API MotorEngine {
	public:
		MotorEngine();
		~MotorEngine();

		/**
		Loads and initializates the engine and the game.
		Automatically loads a _d sufix dll if _DEBUG flags is defined.
		@params gameName Name of the .dll of the game, without any sufixes
		*/
		bool setup(std::string gameName = "VroomVroom");
		void loop();
		void exit();

	private:
		/*
		Load .dll of the Game
		@param gameDllName is the name of the .dll file
		@returns If the game loaded correctly, the function returns true.
		Else, the function will return false.
		*/
		bool loadGame(std::string gameDllname);

		/*
		Creates each component factories and adds them to the componentsFactories map
		*/
		void initFactories();

		/*
		* If we press SDL_QUIT (Exit button), the game stops and closes
		* @param userData is the aditional information of the SDL callback. By default, userData contains nullptr.
		* @param event is a SDL variable that contains information about the SDL_Event launched by any event.
		* @returns is ignored
		*/
		static int quitLoop(void* userdata, SDL_Event* event);

		HMODULE game;

		/*
		* Utils
		*/
		Time* timeUtils;
	};
}

#endif