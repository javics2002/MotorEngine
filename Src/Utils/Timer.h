#pragma once
#ifndef __UTILS_TIMER
#define __UTILS_TIMER

#include "MotorEngine/MotorEngineAPI.h"
#include <string>

namespace me {
	struct TimerData {
		//Real seconds
		float rawSeconds;

		//Convertion to HH:MM:SS.mmm
		int hours, minutes, seconds, milliseconds;
	};

	/*
	Timer will measure time, whether in real seconds or HH:MM:SS.mmm.
	Update must be called every frame.
	*/
	class __MOTORENGINE_API Timer {
		bool mRunning;

		TimerData mTimerData;

	public:
		Timer(bool startNow = true);
		~Timer();

		/*
		Starts or resumes the timer.
		*/
		void resume();

		/*
		Pauses the timer.
		*/
		void pause();

		/*
		Resets the timer to 0.
		*/
		void reset();

		void update(float dt);

		/*
		@returns TimerData struct, includes raw and formatted timer info.
		*/
		TimerData getTimerData();

		/*
		@returns Unformatted seconds of timerData.
		*/
		float getRawSeconds();

		/*
		@param includeHours Whether the hours are removed from the string.
		@returns A string containing the time formatted like HH:MM:SS.mmm.
		*/
		std::string getFormattedTime(bool includeHours = false);
	};
}
#endif