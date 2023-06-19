#include "MotorEngine.h"

#include <thread>

#include "MotorEngineError.h"

#include "Audio/SoundManager.h"
#include "Physics/PhysicsManager.h"
#include "Render/RenderManager.h"
#include "Input/InputManager.h"
#include "SceneManager.h"
#include "Render/RenderWindow.h"
#include "Render/Window.h"

#include "Scene.h"
#include "EntityComponent/ComponentsFactory.h"
#include "EntityComponent/FactoryComponent.h"
#include "EntityComponent/Transform.h"

#include "Scripting/LoadManager.h"

#include "Audio/AudioComponents/AudioListener.h"
#include "Audio/AudioComponents/AudioSource.h"

#include "Physics/PhysicsComponents/Collider.h"
#include "Physics/PhysicsComponents/Rigidbody.h"

#include "Render/RenderComponents/Animator.h"
#include "Render/RenderComponents/Camera.h"
#include "Render/RenderComponents/Light.h"
#include "Render/RenderComponents/MeshRenderer.h"

#include "Render/UIComponents/UIButton.h"
#include "Render/UIComponents/UISpriteRenderer.h"
#include "Render/UIComponents/UITransform.h"
#include "Render/UIComponents/UIText.h"

#include "Utils/Time.h"
#include "Utils/Timer.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>

typedef const char* (*GameName)();
typedef bool(__cdecl* GameEntryPoint)();
typedef void(*TypeDefinition)();
typedef void(*InputDefinition)();

using namespace me;

bool MotorEngine::setup(std::string gameName)
{
	if (!loadGame(gameName)) {
		errorManager().throwMotorEngineError("MotorEngine setup error", "The game dll was not found or is outdated.");
		return false;
	}

	GameEntryPoint entryPoint = (GameEntryPoint)GetProcAddress(mGame, "init");

	if (entryPoint == NULL) {
		FreeLibrary(mGame);

		errorManager().throwMotorEngineError("MotorEngine setup error",
			"Function bool init() in the game dll was not found.");
		return false;
	}

	GameName name = (GameName)GetProcAddress(mGame, "name");

#ifdef _DEBUG
	Window::Init(SDL_INIT_EVERYTHING, name == NULL ? "Motor Engine" : name(), SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
#else
	Window::Init(SDL_INIT_EVERYTHING, name == NULL ? "Motor Engine" : name(), SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_INPUT_FOCUS | 
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
#endif

	// Register Motor Engine's default component factories
	TypeDefinition gameTypesDef = (TypeDefinition)GetProcAddress(mGame, "initFactories");
	if (gameTypesDef == NULL) {
		FreeLibrary(mGame);

		errorManager().throwMotorEngineError("MotorEngine setup error",
			"Function void initFactories() in the game dll was not found.");
		return false;
	}

	// Register Motor Engine's default component factories
	InputDefinition gameInputDef = (InputDefinition)GetProcAddress(mGame, "initInput");
	if (gameInputDef == NULL) {
		FreeLibrary(mGame);

		errorManager().throwMotorEngineError("MotorEngine setup error",
			"Function void initInput() in the game dll was not found.");
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
	mTime = new Time(60);
	
	return entryPoint();
}

void MotorEngine::loop()
{
	bool quit = false;
	inputManager().addEvent(QuitLoop, &quit);
	float dt;

	while (!quit) {
		inputManager().update();
		
		// Update Time Values
		dt = mTime->update();
		
		// Update the scene
		physicsManager().update(dt, 0, 1 / mTime->getTargetFrameRate());

		soundManager().systemRefresh(dt);

		sceneManager().update(dt, quit);

		// Render the scene
		renderManager().render();

		// Wait time
		std::this_thread::sleep_for(std::chrono::milliseconds(mTime->millisecondsToNextFrame()));
	}
}

void MotorEngine::exit()
{
	// Clear the memory created in the execution of the program
	SceneManager::Shutdown();
	LoadManager::Shutdown();
	PhysicsManager::Shutdown();
	RenderManager::Shutdown();
	Window::Shutdown();
	SoundManager::Shutdown();
	ComponentsFactory::Shutdown();
	InputManager::Shutdown();

	if (mTime)
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

	//Convert to wide character string
	std::wstring wName = std::wstring(gameDllName.begin(), gameDllName.end());

	mGame = LoadLibrary(wName.c_str());

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
	componentsFactory().addFactoryComponent("camera", new FactoryCamera());
	componentsFactory().addFactoryComponent("audiosource", new FactoryAudioSource());
	componentsFactory().addFactoryComponent("audiolistener", new FactoryAudioListener());
	componentsFactory().addFactoryComponent("light", new FactoryLight());
	componentsFactory().addFactoryComponent("uitext", new FactoryUIText());
}

int MotorEngine::QuitLoop(void* userdata, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT) {
		bool* quit = (bool*)userdata;
		*quit = true;
	}

	return 0;
}

MotorEngine::MotorEngine() : mGame(nullptr), mTime(nullptr) {
}

MotorEngine::~MotorEngine()
{
}