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
	Time(const float& gameStartTime);
	
	/**
	Function used to update time values
	*/
	void update();

	/**
	Read Only Function used to get the current framerate value
	@returns A float number representing the framerate value (Example: 60fps, 144fps)
	*/
	float getFPS();

	/**
	Read Only Function used to get the current delta time value
	@returns A float number representing the delta time value (Example: 0.016f)
	*/
	float getDeltaTime();

	/**
	Read Only Function used to get the current fixed delta time value
	@returns A float number representing the fixed delta time value (Example: 0.02f)
	*/
	float getFixedDeltaTime();

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
	/*
	Delta time describes the time difference between the previous frame that was drawn and the current frame.
	*/
	float mDeltaTime;

	/*
	Fixed Delta time describes the time difference between the previous PHYSICS frame that was calculated and the current PHYSICS frame.
	*/
	float mFixedDeltaTime;

	/*
	* Current framerate value
	*/
	float mFpsValue; 

	/*
	* Frame counter since the game started
	*/
	unsigned long mFrameCounter;

	/*
	* Time value when game started
	*/
	float mGameStartTime;
};

#endif

