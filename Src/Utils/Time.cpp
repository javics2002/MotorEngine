#include "Time.h"

Time::Time()
{
	// TODO: INIT VARIABLES?
	frameCounter = 0;

	deltaTime = 1 / fpsValue;
}

float Time::getFPS() {
	return frameCounter / gameStartTime * 1000;
}


// TODO: VSYNC
void Time::enableVSYNC()
{

}

void Time::disableVSYNC()
{

}
