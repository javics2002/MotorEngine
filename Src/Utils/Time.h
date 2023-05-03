#pragma once
#ifndef __UTILS_TIME
#define __UTILS_TIME

#include "MotorEngine/MotorEngineAPI.h"

namespace me {
	/*
	class Time provides/has information about time between frames,
	time scale and framerate.
	The default units are seconds and FPS unless specified otherwise.
	Update method must still be called every frame.
	*/
	class __MOTORENGINE_API Time
	{
	public:
		Time(float targetFrameRate = 60, float targetFixedFrameRate = 50, float timeScale = 1);
		~Time();

		/**
		Updates time values.
		@returns Delta Time, or time since last update.
		*/
		double update();

		/*
		@returns Current time since last frame.
		*/
		double getDeltaTime();

		/*
		@returns Current target fixed time between frames.
		*/
		double getFixedDeltaTime();

		/*
		@returns Time left before next frame.
		*/
		double timeToNextFrame();

		/*
		@returns Time left before next frame, in milliseconds.
		*/
		long long millisecondsToNextFrame();

		/**
		Read-Only Function used to get the target frame rate
		@returns A float number representing the target frame rate (Example: 60fps, 144fps)
		*/
		double getTargetFrameRate();

		/*
		Sets the target framerate (time between frames).
		*/
		void setTargetFrameRate(float targetFrameRate);

		/*
		Sets the time scale (running time multiplier, 0.5f would be slow-mo).
		*/
		void setTimeScale(float timeScale);

		/*
		Read-Only: Get the time scale (running time multiplier, 0.5f would be slow-mo).
		@returns Current time scale.
		*/
		float getTimeScale();

		/*
		@returns Current global time in seconds.
		*/
		double obtainCurrentTime();

	private:
		float mTargetFrameRate;
		float mTargetFixedFrameRate;
		float mTargetDeltaTime;
		float mTargetFixedDeltaTime;

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

