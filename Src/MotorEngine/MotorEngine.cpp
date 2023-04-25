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
#include "Render/RenderWindow.h"
#include "Render/Window.h"
// --- Components
#include "EntityComponent/Scene.h"
#include "EntityComponent/Components/ComponentsFactory.h"
#include "EntityComponent/Components/FactoryComponent.h"
// --- Utils
#include "Utils/Time.h"
#include "Utils/Timer.h"
// --- SDL3
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>

typedef const char* (*GameName)();
typedef bool(__cdecl* GameEntryPoint)();
typedef void(*TypeDefinition)();
typedef void(*InputDefinition)();

using namespace me;

bool MotorEngine::setup(std::string gameName)
{
	if (!loadGame(gameName))
		return false;

	GameEntryPoint entryPoint = (GameEntryPoint)GetProcAddress(mGame, "init");

	if (entryPoint == NULL) {
		FreeLibrary(mGame);
		return false;
	}

	GameName name = (GameName)GetProcAddress(mGame, "name");

	Window::Init(SDL_INIT_EVERYTHING, name == NULL ? "Motor Engine" : name(), SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	// Register Motor Engine's default component factories
	TypeDefinition gameTypesDef = (TypeDefinition)GetProcAddress(mGame, "initFactories");
	if (gameTypesDef == NULL) {
		FreeLibrary(mGame);
		return false;
	}

	// Register Motor Engine's default component factories
	InputDefinition gameInputDef = (InputDefinition)GetProcAddress(mGame, "initInput");
	if (gameInputDef == NULL) {
		FreeLibrary(mGame);
		return false;
	}
	
	// Añadir componentes del juego
	gameTypesDef();

	// Añadir componentes del motor
	initFactories();

	// Inicializar Input
	gameInputDef();

	// Init managers
	physicsManager().start();

	// Start time
	mTime = new Time();

	return entryPoint();
}

void MotorEngine::loop()
{
	SDL_Event event;
	bool quit = false;
	inputManager().addEvent(QuitLoop, &quit);
	float dt;

	while (!quit) {
		while (SDL_PollEvent(&event)) { }

		// Update Time Values
		dt = mTime->update();

		// Update the scene
		physicsManager().update(dt);

		sceneManager().update(dt);
		
		// Render the scene
		renderManager().render();
		
		//If we're going to change the scene
		if (sceneManager().isChanging())
			sceneManager().loadScene(sceneManager().getNewScene());

		// Wait time
		std::this_thread::sleep_for(std::chrono::milliseconds(mTime->millisecondsToNextFrame()));
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
	ComponentsFactory::Shutdown();

	delete mTime;

	FreeLibrary(mGame);
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

	mGame = LoadLibrary(wtext);

	delete pReturnValue;
	delete[] wtext;

	return mGame != NULL;
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
