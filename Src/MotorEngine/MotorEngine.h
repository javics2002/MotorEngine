#pragma once
#ifndef __MOTORENGINE_MAIN
#define __MOTORENGINE_MAIN

#define __MOTORENGINE_EXPORT
#ifdef __MOTORENGINE_EXPORT
#define __MOTORENGINE_API __declspec(dllexport)
#else
#define __MOTORENGINE_API __declspec(dllimport)
#endif

#include "Utils/Singleton.h"
#include <Windows.h>
#include <chrono>
#include <string>

union SDL_Event;

extern "C" {
	namespace me {
		/*
		class MotorEngine provides/has information about the characteristics of the Engine,
		as the initialization, main loop and memory management of the program.
		*/
		class __MOTORENGINE_API MotorEngine : public Singleton<MotorEngine> {
		public:
			bool setup();
			void loop();
			void exit();

		private:
			friend Singleton<MotorEngine>;
			MotorEngine();

			//Load dll of the game
			bool loadGame(std::string gameDllname);

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

			HMODULE game;
		};

		__MOTORENGINE_API inline MotorEngine& motorEngine() {
			return *MotorEngine::instance();
		}
	}
}

#endif