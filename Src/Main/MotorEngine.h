#pragma once
#include <chrono>

namespace me {
	class MotorEngine {
	public:
		int setup();
		void loop();
		void quit();

	private:
		// HMODULE game;

		//ECS::Blueprint* blueprintManager;
		//Input::InputManager* inputManager;
		//Renderer::OgreRenderer* ogreManager;
		//Audio::SoundManager* soundManager;
		//Physics::PhysicsManager* physicsManager;

		//SceneManagement::SceneManager* sceneManager;
		//ComponentDefinitions::ComponentFactory* compFactory;
		//LoveEngine::Time* time;
		//lua_State* luastate;

		//int initialiseDLLs(GameComponentDefinition& gcd);
		//int initialiseSceneCreator();

		//void changeWindowTitle();

		void updateTimeValues(
			const std::chrono::steady_clock::time_point& beginFrame,
			const std::chrono::steady_clock::time_point& endFrame,
			const std::chrono::steady_clock::time_point& appStart);
	};
}