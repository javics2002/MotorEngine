#include "MotorEngine.h"

#include <iostream>
#include <thread>
// #include <Windows.h>
#include <time.h>

//#include <PhysicsManager.h>
//#include <OgreRenderer.h>
//#include <SceneManager.h>

#include <memory>
#include <random>
#include "Ogre/OgreManager.h"

namespace me {

	int MotorEngine::setup()
	{
		srand(std::time(NULL)); rand();

		//Manager del proyecto de render
		ogreM();


		//GameComponentDefinition gameComponentDefinitions;

		//if (initialiseDLLs(gameComponentDefinitions)) {
		//	assert(("Error al inicializar las DLL.", false));
		//	return -1;
		//}

		//time = new LoveEngine::Time();
		//sceneManager = new LoveEngine::SceneManagement::SceneManager();
		//compFactory = new LoveEngine::ComponentDefinitions::ComponentFactory();

		////Manager del proyecto de sonido
		//soundManager = new LoveEngine::Audio::SoundManager();

		////Manager del proyecto de fisica
		//physicsManager = new LoveEngine::Physics::PhysicsManager();

		////Manager del proyecto de Input
		//inputManager = new LoveEngine::Input::InputManager();

		//blueprintManager = new LoveEngine::ECS::Blueprint();
		//changeWindowTitle();


		//gameComponentDefinitions();

		//if (initialiseSceneCreator()) {
		//	return -1;
		//}

		//sceneManager->initiliseScenes();
		//sceneManager->initialisePersistentScene();

		return 0;
	}

	void MotorEngine::loop()
	{
		//const float physicsFrameRate = 50;
		//duration pInterval = duration<double>(1.0 / physicsFrameRate);

		//steady_clock::time_point applicationStart = high_resolution_clock::now();
		//steady_clock::time_point lastPhysicFrame = applicationStart;
		//steady_clock::time_point beginFrame = applicationStart;

		//while (true) {

		//	LoveEngine::ECS::Scene* currentScene = sceneManager->getCurrentScene();

		//	if (currentScene == nullptr) {
		//		break;
		//	}

		//	if (!inputManager->handleInput()) { //if SDl Quit, exit the game
		//		break;
		//	}

		//	currentScene->update();
		//	sceneManager->updatePersistentScene();


		//	if ((beginFrame - lastPhysicFrame).count() > physicsFrameRate) {

		//		currentScene->stepPhysics();
		//		physicsManager->update(pInterval.count() * time->timeScale);

		//		lastPhysicFrame = beginFrame;
		//	}

		//	ogreManager->update();

		//	currentScene->removeObjects();

		//	sceneManager->tryChangeScene();

		//	//Calculo del tiempo
		//	steady_clock::time_point endFrame = high_resolution_clock::now();
		//	updateTimeValues(beginFrame, endFrame, applicationStart);
		//	beginFrame = endFrame;
		//}
	}

	void MotorEngine::quit()
	{
		/*delete compFactory;
		delete sceneManager;
		delete time;

		delete physicsManager;
		delete ogreManager;
		delete inputManager;
		delete soundManager;
		delete blueprintManager;

		lua_close(luastate);
		FreeLibrary(game);*/
	}
};