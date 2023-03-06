#include "MotorEngine.h"

#include <iostream>
#include <thread>
#include <Windows.h>
#include <time.h>
#include <chrono>
#include <memory>
#include <random>
#include "Ogre/OgreManager.h"
#include "SDL/InputManager.h"
#include <Ogre.h>
#include <SDL3/SDL_events.h>
#include "SDL/Window.h"
#include <SDL3/SDL_init.h>
#include "Bullet/PhysicsManager.h"
#include "Utils/Vector3.h"
#include "Ogre/OgreManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/RigidBody.h"
#include "EntityComponent/MeshRenderer.h"
#include "EntityComponent/Collider.h"
#include "FMOD/SoundManager.h"

int interact(void* userdata)
{
	std::cout << "Interacting!\n";

	return 0;
}

int toggleInteract(void* userdata)
{
	bool* interactActive = (bool*)userdata;
	if (*interactActive)
		me::im().deleteOnButtonPressedEvent("Interact", interact, NULL);
	else
		me::im().addOnButtonPressedEvent("Interact", interact, NULL);

	*interactActive = !*interactActive;

	return 0;
}

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

int getAxisValue(void* userdata) {
	char* name = (char*)userdata;
	std::cout << name << " axis value: " << me::im().getAxis(name) << "\n";

	return 0;
}

namespace me {
	int MotorEngine::setup()
	{
		Window::init(SDL_INIT_EVERYTHING, "Motor Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		//Manager del proyecto de render
		std::string camJ1 = "CameraJugador1";
		om().createCamera(camJ1, 5, 10000, true, 0, Ogre::ColourValue(0.0f, 0.0f, 0.1f));
		om().setCameraInfo(camJ1, Ogre::Vector3f(0, 200, 500), Ogre::Vector3(0, -1, -1));
		om().createNewLight("Luz", Ogre::Vector3f(0, 500, 500), Ogre::Vector3f(0, -1, -1));

		pm().start();

		plane = new Entity("plane");

		auto tr = plane->addComponent<Transform>("transform");
		tr->setPosition(Vector3(0, -50, 0));
		tr->setScale(Vector3(5, 0.1, 5));

		plane->addComponent<RigidBody>("rigidBody", 1, 1, 5, 0.3, 0.5, false);
		plane->addComponent<MeshRenderer>("meshRenderer", "p", "cube.mesh")->setMaterial("Material/roja");

		cube = new Entity("cube");

		cube->addComponent<Transform>("transform")->setPosition(Vector3(0, 200, 0));

		cube->addComponent<RigidBody>("rigidBody", 1, 0, 5, 0.3, 0.5, false);
		cube->addComponent<MeshRenderer>("meshRenderer", "c", "cube.mesh")->setMaterial("Material/marronclaro");

		om().scene1();

		Input keyboardE;
		keyboardE.type = INPUTTYPE_KEYBOARD;
		keyboardE.which = SDLK_e;

		im().addButton("Interact", keyboardE);

		static bool interactActive = false;

		Input keyboardSpace;
		keyboardSpace.type = INPUTTYPE_KEYBOARD;
		keyboardSpace.which = SDLK_SPACE;
		im().addButton("Space", keyboardSpace);

		im().addOnButtonPressedEvent("Space", toggleInteract, &interactActive);

		Input controllerA;
		controllerA.type = INPUTTYPE_GAMEPAD_BUTTON;
		controllerA.which = SDL_GAMEPAD_BUTTON_A;

		im().addButton("A", controllerA);

		im().addOnButtonPressedEvent("A", shoot);

		AxisInput horizontal;
		horizontal.type = INPUTTYPE_KEYBOARD;
		horizontal.positive = SDLK_d;
		horizontal.negative = SDLK_a;

		AxisInfo horizontalInfo;
		horizontalInfo.dead = .1;
		horizontalInfo.gravity = .01;

		char* horizontalName = (char*)"Horizontal";
		im().addAxis(horizontalName, horizontalInfo, horizontal);

		Input keyboardP;
		keyboardP.type = INPUTTYPE_KEYBOARD;
		keyboardP.which = SDLK_p;

		im().addButton("P", keyboardP);
		im().addOnButtonPressedEvent("P", getAxisValue, horizontalName);

		std::cout << "Use Space to toogle Interact. Use E to interact when Interact is enabled.\n";

		result = FMOD::System_Create(&Sound_System);      // Create the main system object.
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			std::exit(-1);
		}

		result = Sound_System->init(MAX_CHANNELS, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			std::exit(-1);
		}

		result = Sound_System->createSound("Assets/Sounds/wave.mp3", FMOD_DEFAULT, 0, &sonido);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			std::exit(-1);
		}

		result = Sound_System->createSound("Assets/Sounds/fire.wav", FMOD_DEFAULT, 0, &disparo);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			std::exit(-1);
		}

		result = Sound_System->playSound(sonido, 0, false, &canal1);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			std::exit(-1);
		}

		static TestSound testSound;

		testSound.system = Sound_System;
		testSound.sound = disparo;
		testSound.channel = canal1;

		Input leftClick;
		leftClick.type = INPUTTYPE_MOUSE_CLICK;
		leftClick.which = SDL_BUTTON_LEFT;
		im().addButton("Shoot", leftClick);

		im().addOnButtonPressedEvent("Shoot", shoot, &testSound);
		
		return 0;
	}

	void MotorEngine::loop()
	{
		/*
		Physics are calculated every 0.02 seconds (Fixed Update) while the rest of the game is calculated depending on the frames per second 
		of the computer
		*/
		const float pFrameRate = 50;
		std::chrono::duration<double> pInterval = std::chrono::duration<double>(1.0 / pFrameRate);

		/*
		* Three clocks that are used to calculate time between frames
		*/
		std::chrono::steady_clock::time_point gameStartFrame = std::chrono::high_resolution_clock::now();
		std::chrono::steady_clock::time_point beginFrame = gameStartFrame;
		std::chrono::steady_clock::time_point lastPhysicFrame = gameStartFrame;

		SDL_Event event;
		bool quit = false;
		im().addEvent(quitLoop, &quit);
		while (!quit) {
			while(SDL_PollEvent(&event)) {

			}

			/*
			* Update the scene
			*/
			pm().update(0.0166);
			plane->update();
			cube->update();
			result = Sound_System->update();
			if (result != FMOD_OK)
			{
				printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
				std::exit(-1);
			}
			
			/*
			* Update physics
			*/
			if ((beginFrame - lastPhysicFrame).count() > pFrameRate) {

				/*currentScene->stepPhysics();
				physicsManager->update(pInterval.count() * time->timeScale);*/

				lastPhysicFrame = beginFrame;
			}

			/*
			* Render the scene
			*/
			om().render();

			/*
			* Update the new frames values
			*/
			std::chrono::steady_clock::time_point endFrame = std::chrono::high_resolution_clock::now();
			updateTimeValues(beginFrame, endFrame, gameStartFrame);
			beginFrame = endFrame;
		}
	}

	void MotorEngine::exit()
	{
		/*
		Clear the memory created in the execution of the program
		*/

		//delete ogreManager;
	}

	void MotorEngine::updateTimeValues(const std::chrono::steady_clock::time_point& beginFrame, 
		const  std::chrono::steady_clock::time_point& endFrame, const  std::chrono::steady_clock::time_point& gameStartFrame)
	{
		std::chrono::duration<float, std::milli> timeSinceStart = endFrame - gameStartFrame;
		std::chrono::duration<double, std::milli> timeSinceLastFrame = endFrame - beginFrame;

		//time->timeSinceStart = timeSinceStart.count();
		//time->deltaTime = timeSinceLastFrame.count() * 0.001;
		//time->frameCount++;
	}

	int MotorEngine::quitLoop(void* userdata, SDL_Event* event)
	{
		if (event->type == SDL_EVENT_QUIT || (event->type == SDL_EVENT_KEY_DOWN && event->key.keysym.sym == SDLK_ESCAPE)) {
			bool* quit = (bool*)userdata;
			*quit = true;

#ifdef _DEBUG
			std::cout << "MotorEngine quitting...\n";
#endif
		}

		return 0;
	}
};