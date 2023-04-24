#pragma once
#ifndef __UTILS_TIME
#define __UTILS_TIME

#include "MotorEngine/MotorEngineAPI.h"

namespace me {
	/*
	class Time provides/has information about time between frames,
	time scale and framerate.
	The default units are seconds and FPS unless specified otherwise.
	The user has to call the update method everyframe
	*/
	class __MOTORENGINE_API Time
	{
	public:
		Time(float targetFrameRate = 60, float timeScale = 1);
		~Time();

		/**
		Updates time values.
		@returns Delta Time, or time since last update.
		*/
		double update();

		double getDeltaTime();

		double timeToNextFrame();
		long long millisecondsToNextFrame();

		/**
		Read Only Function used to get the target frame rate
		@returns A float number representing the target frame rate (Example: 60fps, 144fps)
		*/
		double getTargetFrameRate();
		void setTargetFrameRate(float targetFrameRate);

		void setTimeScale(float timeScale);
		float getTimeScale();

		/*
		@returns Current global time in seconds
		*/
		double obtainCurrentTime();

	protected:
		float mTargetFrameRate;

		double mPreviousFrameTime;
		double mCurrentFrameTime;

		/*
		Delta time describes the time difference between 
		the previous frame that was drawn and the current frame.
		*/
		double mDeltaTime;

		float mTimeScale;
	};
}
#endif

