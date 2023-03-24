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

	/**
	Read Only Function used to get the framerate value
	@returns A float number representing the framerate value (Example: 60fps, 144fps)
	*/
	float getGameFrameValue();

	/**
	Read Only Function used to get the physics framerate value
	@returns A float number representing the framerate value (Example: 50.0f)
	*/
	float getPhysicsFrameValue();

	/**
	Function used to enable vertical syncronization to cap the framerate of the game
	*/
	void enableVSYNC();

	/**
	Function used to disable vertical syncronization to uncap the framerate of the game
	*/
	void disableVSYNC();

	/*
	Delta time describes the time difference between the previous frame that was drawn and the current frame.
	*/
	double deltaTime;

	/*
	Fixed Delta time describes the time difference between the previous PHYSICS frame that was calculated and the current PHYSICS frame.
	*/
	double fixedDeltaTime;

	/*
	* Current Framerate value
	*/
	float currentFPSValue;

private:
protected:

	/*
	* Framerate value (60, 144)
	*/
	float mFrameValue; 

	/*
	*  Physics framerate value (50)
	*/
	float mPhysicsFrameValue;
};

#endif

