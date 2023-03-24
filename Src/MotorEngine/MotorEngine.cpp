#include "MotorEngine.h"

// --- C++
#include <iostream>
#include <thread>
#include <time.h>
#include <memory>
#include <random>
// --- Managers
#include "Audio/SoundManager.h"
#include "Physics/PhysicsManager.h"
#include "Render/RenderManager.h"
#include "Input/InputManager.h"
#include "EntityComponent/SceneManager.h"
#include "EntityComponent/Scene.h"
#include "Render/Window.h"
// --- Components
#include "EntityComponent/Components/ComponentsFactory.h"
#include "EntityComponent/Components/FactoryComponent.h"
// --- Utils
#include "Utils/Time.h"
// --- SDL3
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>

//typedef HRESULT(CALLBACK* LPFNDLLFUNC1)(DWORD, UINT*);
typedef const char* (*GameName)();
typedef bool(__cdecl* GameEntryPoint)();
typedef void(*TypeDefinition)();

using namespace me;

bool MotorEngine::setup(std::string gameName)
{
	loadGame(gameName); 

	//if (game == NULL)
	//	return false;

	//GameEntryPoint entryPoint = (GameEntryPoint)GetProcAddress(game, "init");

	//if (entryPoint == NULL)
	//	return false;

	//GameName name = (GameName)GetProcAddress(game, "name");

	//Window::init(SDL_INIT_EVERYTHING, name == NULL ? "Motor Engine" : name(), SDL_WINDOWPOS_UNDEFINED,
	//	SDL_WINDOWPOS_UNDEFINED, 854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	//// Register Motor Engine's default component factories
	//TypeDefinition gameTypesDef = (TypeDefinition)GetProcAddress(game, "initFactories");
	//if (gameTypesDef == NULL)
	//	return false;
	//
	//// Añadir componentes del juego
	//gameTypesDef();

	//// Añadir componentes del motor
	//initFactories();
	//
	//// Register game's component factories
	//TypeDefinition gameTypesDef = (TypeDefinition)GetProcAddress(game, "initFactories");
	//if (gameTypesDef != NULL)
	//	gameTypesDef();

	// Init managers
	physicsManager().start();
	std::string cam = "CameraDemo";
	renderManager().createCamera(cam, 5, 10000, true, 0, Ogre::ColourValue(0, 0, 0.5));
	renderManager().setCameraInfo(cam, Ogre::Vector3f(0, 200, 500), Ogre::Vector3f(0, -1, -1));
	// entryPoint();

	return 0;
	// return entryPoint();
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

	sceneManager().getActiveScene().get()->processNewEntities();
	sceneManager().getActiveScene().get()->start();
	// Init Utils
	// std::cout << gameStartFrame << "\n";
	//float test = std::chrono::duration_cast<float, std::chrono::steady_clock::time_point>(gameStartFrame);
	// timeUtils = new Time(test);

	SDL_Event event;
	bool quit = false;
	inputManager().addEvent(quitLoop, &quit);
	while (!quit) {
		while (SDL_PollEvent(&event)) {

		}

		timeUtils->update();

		/*
		* Update the scene
		*/
		physicsManager().update(0.0166);
		sceneManager().update();
		std::cout << timeUtils->getFPS() << "\n";
		// physicsManager().update(timeUtils->getDeltaTime());
		

		/*
		* Update physics
		*/
		if ((beginFrame - lastPhysicFrame).count() > pFrameRate) 
			lastPhysicFrame = beginFrame;

		/*
		* Render the scene
		*/
		// renderManager().render();

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
	componentsFactory().addFactoryComponent("transform", new FactoryTransform());
	componentsFactory().addFactoryComponent("rigidbody", new FactoryRigidBody());
	componentsFactory().addFactoryComponent("animator", new FactoryAnimator());
	componentsFactory().addFactoryComponent("meshrenderer", new FactoryMeshRenderer());
	componentsFactory().addFactoryComponent("collider", new FactoryCollider());
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

MotorEngine::~MotorEngine()
{
}
