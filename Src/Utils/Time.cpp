#include "Time.h"

Time::Time(const float& gameStartTime)
{
	mFrameCounter = 0;
	mFpsValue = 0;
	mDeltaTime = 0;
	mFixedDeltaTime = 0;
	mGameStartTime = gameStartTime;
}

float Time::getFPS() {
	return mFpsValue;
}


float Time::getDeltaTime()
{
	return mDeltaTime;
}

float Time::getFixedDeltaTime()
{
	return mFixedDeltaTime;
}

void Time::update()
{
	mFrameCounter++; // Adds 1 frame
	mFpsValue = mFrameCounter / mGameStartTime * 1000; // Updates fps value

	mDeltaTime = 1 / mFpsValue; // Update delta time

	// TODO: Update fixed delta time

}


// TODO: VSYNC
void Time::enableVSYNC()
{

}

void Time::disableVSYNC()
{

}

