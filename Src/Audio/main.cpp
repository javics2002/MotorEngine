#include <iostream>
#include <stdio.h>
//#include "Utils/checkML.h"

#include "SoundManager.h"
#include "Input/InputManager.h"
#include "Render/Window.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_gamepad.h>

using namespace me;

struct TestSound {
	FMOD::Sound* sound;
	FMOD::Channel* channel;
	FMOD::System* system;
};

int shoot(void* userdata)
{
	std::cout << "Shooting!\n";

	TestSound test = *(TestSound*)userdata;

	//test.system->playSound(test.sound, 0, false, &test.channel);

	return 0;
}

int main() {
	std::cout << "HOlA";
	FMOD_RESULT result;
	//FMOD_SOUND sonido{};
	FMOD::System* Sound_System = NULL;
	FMOD::Sound* doppler, * disparo;
	FMOD::Channel* canal1 = nullptr;
	me::soundManager();
	me::inputManager();

	me::Window::init(SDL_INIT_EVERYTHING, "Sound Manager Test",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 854, 480, SDL_WINDOW_INPUT_FOCUS);
	
	

	
	
	//soundManager().createNormalSound("Assets/Sounds/fire.wav", disparo);

	//soundManager().create3DSound("Assets/Sounds/wave.mp3", doppler, 0.5f * DISTANCE_FACTOR, 5000.0f* DISTANCE_FACTOR);
	

	static TestSound testSound;

	testSound.system = Sound_System;
	//testSound.sound = disparo;
	testSound.channel = canal1;

	me::Input botonA;
	botonA.type = me::INPUTTYPE_KEYBOARD;
	botonA.which = SDLK_a;
	me::inputManager().addButton("Shoot", botonA);

	bool what = me::inputManager().addOnButtonPressedEvent("Shoot", shoot, &testSound);
	SDL_Event event;
	while (true) {
		//std::cout << "bucle" << std::endl;
			while (SDL_PollEvent(&event)) {

			}
			soundManager().systemRefresh();
			
	}
	return 0;

	
}