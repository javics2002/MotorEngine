#include <iostream>
#include <stdio.h>
//#include "Utils/checkML.h"

#include <fmod.hpp>
#include <fmod_errors.h>
#include "SoundManager.h"
#include "Input/InputManager.h"
#include "Render/Window.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_gamepad.h>

const int MAX_CHANNELS = 36;

struct TestSound {
	FMOD::Sound* sound;
	FMOD::Channel* channel;
	FMOD::System* system;
};

int shoot(void* userdata)
{
	std::cout << "Shooting!\n";

	TestSound test = *(TestSound*)userdata;

	test.system->playSound(test.sound, 0, false, &test.channel);

	return 0;
}

int main() {
	std::cout << "HOlA";
	FMOD_RESULT result;
	//FMOD_SOUND sonido{};
	FMOD::System* Sound_System = NULL;
	FMOD::Sound* sonido, * disparo;
	FMOD::Channel* canal1 = nullptr;
	//me::SoundManager &sm  = me::sm();

	me::im();
	me::Window::init(SDL_INIT_EVERYTHING, "Sound Manager Test",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 854, 480, SDL_WINDOW_INPUT_FOCUS);
	
	

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
	
	result = Sound_System->createSound("Assets/Sounds/fire.wav", FMOD_DEFAULT, 0, &disparo);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	/*result = Sound_System->playSound(sonido, 0, false, &canal1);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}*/
	

	static TestSound testSound;

	testSound.system = Sound_System;
	testSound.sound = disparo;
	testSound.channel = canal1;

	me::Input botonA;
	botonA.type = me::INPUTTYPE_KEYBOARD;
	botonA.which = SDLK_a;
	me::im().addButton("Shoot", botonA);

	bool what = me::im().addOnButtonPressedEvent("Shoot", shoot, &testSound);
	SDL_Event event;
	while (true) {
		//std::cout << "bucle" << std::endl;
			while (SDL_PollEvent(&event)) {

			}
			result = Sound_System->update();
			if (result != FMOD_OK)
			{
				printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
				exit(-1);
			}
	}
	return 0;

	
}