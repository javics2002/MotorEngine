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
#include "EntityComponent/Entity.h" //Borrar
#include "EntityComponent/Components/Transform.h" //Borrar

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

	if (game == NULL)
		return false;

	GameEntryPoint entryPoint = (GameEntryPoint)GetProcAddress(game, "init");

	if (entryPoint == NULL)
		return false;

	GameName name = (GameName)GetProcAddress(game, "name");

	Window::init(SDL_INIT_EVERYTHING, name == NULL ? "Motor Engine" : name(), SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	// Register Motor Engine's default component factories
	TypeDefinition gameTypesDef = (TypeDefinition)GetProcAddress(game, "initFactories");
	if (gameTypesDef == NULL)
		return false;
	
	// Añadir componentes del juego
	gameTypesDef();

	// Añadir componentes del motor
	initFactories();

	// Init managers
	physicsManager().start();
	std::string cam = "CameraDemo";
	renderManager().createCamera(cam, 1, 10000, true, 0, Ogre::ColourValue(0, 0, 0.5));
	renderManager().setCameraInfo(cam, Ogre::Vector3f(0, 0.45, -0.8), Ogre::Vector3f(-1000, 0, 0));
	renderManager().createNewLight("luz", Ogre::Vector3f(0, 500, 500), Ogre::Vector3f(0, -1, -1));

	return entryPoint();
}

void MotorEngine::loop()
{
	/*
	Init Utils
	*/
	timeUtils = new Time();
	
	/*
	Physics are calculated every 0.02 seconds (Fixed Update) while the rest of the game is calculated depending on the frames per second
	of the computer
	*/
	float pFrameRate = timeUtils->getPhysicsFrameValue();
	std::chrono::duration<double> pInterval = std::chrono::duration<double>(1.0 / pFrameRate); // -> 1 / 50

	/*
	* Two clocks that are used to calculate time between frames
	*/
	std::chrono::steady_clock::time_point lastTick = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point lastPhysicsTick = std::chrono::high_resolution_clock::now();

	/*
	* Used to calculate Delta Time and Fixed Delta Time
	*/
	std::chrono::duration<double> dtAccum = std::chrono::duration<double>();
	std::chrono::duration<double> dt = std::chrono::duration<double>();
	std::chrono::duration<double> fixedDt = std::chrono::duration<double>();

	/*
	* FrameRate counter
	*/
	std::chrono::duration<double> timer = std::chrono::duration<double>();
	unsigned int frameCounter = 0;
	double fpsValue = 0;

	sceneManager().getActiveScene().get()->processNewEntities();
	sceneManager().getActiveScene().get()->start();
	
	SDL_Event event;
	bool quit = false;
	inputManager().addEvent(quitLoop, &quit);
	while (!quit) {
		while (SDL_PollEvent(&event)) {

		}

		/*
		* Update the new frames values
		*/
		dt = std::chrono::high_resolution_clock::now() - lastTick;
		timer += dt;
		timeUtils->deltaTime = dt.count();

		// FPS
		frameCounter++;
		if (timer.count() > 1.0) { //every second
			fpsValue = frameCounter / 1000;
			timeUtils->currentFPSValue = fpsValue;

			std::cout << "FPS:" << timeUtils->currentFPSValue << std::endl;
			
			frameCounter = 0;
			timer = std::chrono::duration<double>();
		}

		/*
		* Update the scene
		*/
		sceneManager().update();
		
		/*
		* Update physics
		*/
		dtAccum += dt;
		physicsManager().update(0.016);

		if (dtAccum >= pInterval) { // Limitado a 50 fps
			fixedDt = std::chrono::high_resolution_clock::now() - lastPhysicsTick;
			timeUtils->fixedDeltaTime = fixedDt.count();

			dtAccum = std::chrono::duration<double>();

			lastPhysicsTick = std::chrono::high_resolution_clock::now();
		}

		/*
		* Render the scene
		*/
		renderManager().render();

		lastTick = std::chrono::high_resolution_clock::now();
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
