#pragma once
#ifndef __MOTORENGINE_MAIN
#define __MOTORENGINE_MAIN

#include <chrono>

namespace me {
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
	};
}

#endif