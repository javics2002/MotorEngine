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
#include "Render/Window.h"
// --- Components
#include "EntityComponent/Components/ComponentsFactory.h"
#include "EntityComponent/Components/FactoryComponent.h"
// --- Utils
#include "Utils/Time.h"
// --- SDL3
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include "Render/RenderWindow.h"


#include "EntityComponent/Scene.h"


//typedef HRESULT(CALLBACK* LPFNDLLFUNC1)(DWORD, UINT*);
typedef const char* (*GameName)();
typedef bool(__cdecl* GameEntryPoint)();
typedef void(*TypeDefinition)();
typedef void(*InputDefinition)();

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

	Window::Init(SDL_INIT_EVERYTHING, name == NULL ? "Motor Engine" : name(), SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	// Register Motor Engine's default component factories
	TypeDefinition gameTypesDef = (TypeDefinition)GetProcAddress(game, "initFactories");
	if (gameTypesDef == NULL)
		return false;

	// Register Motor Engine's default component factories
	InputDefinition gameInputDef = (InputDefinition)GetProcAddress(game, "initInput");
	if (gameInputDef == NULL)
		return false;
	
	// Añadir componentes del juego
	gameTypesDef();

	// Añadir componentes del motor
	initFactories();

	// Inicializar Input
	gameInputDef();

	// Init managers
	physicsManager().start();

	return entryPoint();
}

void MotorEngine::loop()
{
	//sceneManager().getActiveScene()->processNewEntities();
	//sceneManager().getActiveScene()->start();

	/*
	Init Time Utils
	*/
	timeUtils = new Time();

	double prevTime = timeUtils->obtainActualTime();
	double actTime = 0.0;

	SDL_Event event;
	bool quit = false;
	inputManager().addEvent(QuitLoop, &quit);
	while (!quit) {
		while (SDL_PollEvent(&event)) {

		}

		/*
		* Update Time Values
		*/ 
		actTime = timeUtils->obtainActualTime();
		timeUtils->deltaTime = actTime - prevTime;
		prevTime = actTime;

		/*
		* Update the scene
		*/
		sceneManager().update();

		physicsManager().update(timeUtils->deltaTime);
		
		/*
		* Render the scene
		*/

		// renderManager().createSprite("a", "a");
		renderManager().render();

		/*
		* Wait time
		*/
		std::this_thread::sleep_for(std::chrono::milliseconds(16)); // 16ms para apuntar a 60 FPS (1000ms / 60FPS = ~16ms)
	}
}

void MotorEngine::exit()
{
	/*
	Clear the memory created in the execution of the program
	*/

	sceneManager().deleteAllScenes();

	RenderManager::Shutdown();
	SceneManager::Shutdown();
	PhysicsManager::Shutdown();
	InputManager::Shutdown();
	Window::Shutdown();
	SoundManager::Shutdown();

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
	componentsFactory().addFactoryComponent("uitransform", new FactoryUITransform());
	componentsFactory().addFactoryComponent("rigidbody", new FactoryRigidBody());
	componentsFactory().addFactoryComponent("animator", new FactoryAnimator());
	componentsFactory().addFactoryComponent("meshrenderer", new FactoryMeshRenderer());
	componentsFactory().addFactoryComponent("uispriterenderer", new FactoryUISpriteRenderer());
	componentsFactory().addFactoryComponent("collider", new FactoryCollider());
	componentsFactory().addFactoryComponent("particlesystem", new FactoryParticleSystem());
	componentsFactory().addFactoryComponent("camera", new FactoryCamera());
	componentsFactory().addFactoryComponent("audiosource", new FactoryAudioSource());
	componentsFactory().addFactoryComponent("audiolistener", new FactoryAudioListener());
	componentsFactory().addFactoryComponent("light", new FactoryLight());
}

int MotorEngine::QuitLoop(void* userdata, SDL_Event* event)
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
