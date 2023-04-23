#include "Timer.h"
#include <sstream>
#include <iomanip>

using namespace me;

Timer::Timer(bool startNow) : mRunning(startNow)
{
	reset();
}

Timer::~Timer()
{
}

void Timer::resume()
{
	mRunning = true;
}

void Timer::pause()
{
	mRunning = false;
}

void Timer::reset()
{
	mTimerData.rawSeconds = 0;
	mTimerData.hours = mTimerData.minutes = mTimerData.seconds = mTimerData.milliseconds = 0;
}

void Timer::update(float dt)
{
	if (mRunning) {
		mTimerData.rawSeconds += dt;
		mTimerData.hours = (int)(mTimerData.rawSeconds / 3600);
		mTimerData.minutes = (int)((mTimerData.rawSeconds - (mTimerData.hours * 3600)) / 60);
		mTimerData.seconds = (int)(mTimerData.rawSeconds - (mTimerData.hours * 3600) - (mTimerData.minutes * 60));
		mTimerData.milliseconds = (int)((mTimerData.rawSeconds - (int)mTimerData.rawSeconds) * 1000);
	}
}

TimerData Timer::getTimerData()
{
	return mTimerData;
}

float Timer::getRawSeconds()
{
	return mTimerData.rawSeconds;
}

std::string Timer::getFormattedTime(bool includeHours)
{
	std::ostringstream formattedTime;

	if (includeHours)
		formattedTime << std::setfill('0') << std::setw(2) << mTimerData.hours << ":";

	formattedTime << std::setfill('0') << std::setw(2) << mTimerData.minutes << ":"
		<< std::setfill('0') << std::setw(2) << mTimerData.seconds << "."
		<< std::setfill('0') << std::setw(3) << mTimerData.milliseconds;

	return formattedTime.str();
}
