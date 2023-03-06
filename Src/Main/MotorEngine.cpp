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

int shoot(void* userdata)
{
	std::cout << "Shooting!\n";

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
		om().setCameraInfo(camJ1, Ogre::Vector3f(0, 0, 500), Ogre::Vector3(0, 0, -1));
		om().createNewLight("Luz", Ogre::Vector3f(0, 500, 500), Ogre::Vector3f(0, -1, -1));

		std::string sinbadEnt = "Sinbad";
		om().createMesh(sinbadEnt,"Sinbad.mesh");
		om().setMeshTransform(sinbadEnt, Ogre::Vector3f(0, 0, 0), Ogre::Vector3f(10, 10, 10));

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

		Input leftClick;
		leftClick.type = INPUTTYPE_MOUSE_CLICK;
		leftClick.which = SDL_BUTTON_LEFT;
		im().addButton("Shoot", leftClick);

		im().addOnButtonPressedEvent("Shoot", shoot);

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