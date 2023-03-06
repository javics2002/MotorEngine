#include <iostream>
#include <stdio.h>

//#include <fmod.hpp>
//#include <fmod_errors.h>
#include "SoundManager.h"

const int MAX_CHANNELS = 36;

int main() {
	std::cout << "HOlA";
	FMOD_RESULT result;
	//FMOD_SOUND sonido{};
	FMOD::System* Sound_System = NULL;
	FMOD::Sound* sonido;
	FMOD::Channel* canal1;
	//me::SoundManager &sm  = me::sm();

	

	

	result = FMOD::System_Create(&Sound_System);      // Create the main system object.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = Sound_System->init(MAX_CHANNELS, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
	
	result = Sound_System->createSound("Assets/Sounds/wave.mp3", FMOD_DEFAULT, 0, &sonido);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = Sound_System->playSound(sonido, 0, false, &canal1);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
	while (true) {
		result = Sound_System->update();
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}
	}

	return 0;

	
}