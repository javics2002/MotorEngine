#pragma once
#ifndef __MOTORENGINE_MAIN
#define __MOTORENGINE_MAIN

#include "Audio/SoundManager.h"
#include <Windows.h>
#include <chrono>

union SDL_Event;

namespace me {
	class Entity;
	class OgreManager;

	/*
	class MotorEngine provides/has information about the characteristics of the Engine,
	as the initialization, main loop and memory management of the program.
	*/
	class MotorEngine {
	public:
		int setup();
		void loop();
		void exit();

	private:
		OgreManager* ogreManager; // All information related to graphics and render.

		/**
		Function used to update the values of the frames
		@param beginFrame is the time value of the frame before the execution of the main loop
		@param endFrame is the time value of the frame after the execution of the main loop
		@param gameStartFrame is the time value of the frame that was executed when the game was initialized
		*/
		void updateTimeValues(const std::chrono::steady_clock::time_point& beginFrame,
			const std::chrono::steady_clock::time_point& endFrame, const std::chrono::steady_clock::time_point& gameStartFrame);

		/*
		* If we press SDL_QUIT (Exit button), the game stops and closes
		*/
		static int quitLoop(void* userdata, SDL_Event* event);

		//Load dll of the game
		bool loadGame(std::string gameDllname);

		HMODULE game;

		//Test hito 1
		Entity* plane, *cube;
		Entity* camera1, *camera2;
		FMOD_RESULT result;
		FMOD::System* Sound_System = NULL;
		FMOD::Sound* sonido, *disparo;
		FMOD::Channel* canal1;
	};
}

#endif