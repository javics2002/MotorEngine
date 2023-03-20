#include "MotorEngine.h"

#include <iostream>
#include <thread>
#include <time.h>
#include <memory>
#include <random>
#include "Audio/SoundManager.h"
#include "Physics/PhysicsManager.h"
#include "Render/OgreManager.h"
#include "Input/InputManager.h"
#include "EntityComponent/SceneManager.h"
#include "Render/Window.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>

//typedef HRESULT(CALLBACK* LPFNDLLFUNC1)(DWORD, UINT*);
typedef const char* (*GameName)();
typedef bool(__cdecl* GameEntryPoint)();

using namespace me;

bool MotorEngine::setup()
{
	loadGame("VroomVroom"); //Deberia subir la variable a setup

	if (game == NULL)
		return false;

	GameEntryPoint entryPoint = (GameEntryPoint)GetProcAddress(game, "init");

	if (entryPoint == NULL)
		return false;

	GameName name = (GameName)GetProcAddress(game, "name");

	Window::init(SDL_INIT_EVERYTHING, name == NULL ? "Motor Engine" : name(), SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	entryPoint();

	return true;
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
	inputManager().addEvent(quitLoop, &quit);
	while (!quit) {
		while (SDL_PollEvent(&event)) {

		}

		/*
		* Update the scene
		*/
		physicsManager().update(0.0166);
		

		/*
		* Update physics
		*/
		if ((beginFrame - lastPhysicFrame).count() > pFrameRate) 
			lastPhysicFrame = beginFrame;

		/*
		* Render the scene
		*/
		renderManager().render();

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

	FreeLibrary(game);
}

bool MotorEngine::loadGame(std::string gameDllName)
{
#ifdef _DEBUG
	gameDllName = "./" + gameDllName + "_d.dll";
#else
	gameDllName = "./" + gameDllName + ".dll";
#endif

	//Convert to Windows text
	size_t length = gameDllName.length();
	wchar_t* wtext = new wchar_t[length * 2];

	size_t* pReturnValue = new size_t();
	mbstowcs_s(pReturnValue, wtext, length * 2, gameDllName.c_str(), length);

	game = LoadLibrary(wtext);

	delete pReturnValue;
	delete[] wtext;

	return game != NULL;
}

void me::MotorEngine::initFactories()
{
	
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

MotorEngine::MotorEngine() {

}