#include "Time.h"
#include <chrono>

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

// Función para obtener el tiempo actual en segundos
double Time::obtainActualTime() {
	return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}


