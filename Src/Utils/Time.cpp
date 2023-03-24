#include "Time.h"

Time::Time()
{
	mFrameValue = 60;
	mPhysicsFrameValue = 50;
}

float Time::getGameFrameValue()
{
	return mFrameValue;
}

float Time::getPhysicsFrameValue()
{
	return mPhysicsFrameValue;
}

// TODO: VSYNC
void Time::enableVSYNC()
{

}

void Time::disableVSYNC()
{

}

