#pragma once
#ifndef __UTILS_TIME
#define __UTILS_TIME

#include "MotorEngine/MotorEngineAPI.h"

/*
class Time provides/has information about time between frames, 
physics time between frames, time scale and framerate.
*/
class __MOTORENGINE_API Time
{
public:
	Time();
	
	/*
	Delta time describes the time difference between the previous frame that was drawn and the current frame.
	*/
	float deltaTime;

	/*
	Fixed Delta time describes the time difference between the previous PHYSICS frame that was calculated and the current PHYSICS frame.
	*/
	float fixedDeltaTime;

	/**
	Read Only Function used to get the current framerate value
	@returns A float number representing the framerate value (Example: 60fps, 144fps)
	*/
	float getFPS();

	/**
	Function used to enable vertical syncronization to cap the framerate of the game
	*/
	void enableVSYNC();

	/**
	Function used to disable vertical syncronization to uncap the framerate of the game
	*/
	void disableVSYNC();

private:
protected:
	float fpsValue; // Current framerate value
	unsigned long frameCounter; // Frame counter since the game started
	float gameStartTime; // Time value when game started
};

#endif

