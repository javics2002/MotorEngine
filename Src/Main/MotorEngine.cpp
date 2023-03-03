#include "MotorEngine.h"

#include <iostream>
#include <thread>
#include <Windows.h>
#include <time.h>
#include <chrono>
#include <memory>
#include <random>
#include "Ogre/OgreManager.h"

namespace me {

	int MotorEngine::setup()
	{
		srand(std::time(NULL)); rand();

		//Manager del proyecto de render
		 om();
		 std::string camJ1 = "CameraJugador1";

		 om().createCamera(camJ1, 5, 10000, true, 0);
		 om().setCameraInfo(camJ1, *om().createVector( 0, 0, 500), *om().createVector(0, 0, -1));
		 om().createNewLight("Luz", *om().createVector(0, 500, 500), *om().createVector(0, -1, -1));

		 std::string sinbadEnt = "Sinbad";
		 om().createMesh(sinbadEnt,"Sinbad.mesh");
		 om().setMeshTransform(sinbadEnt, *om().createVector(0, 0, 0), *om().createVector(10, 10, 10));
		 
		

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

		while (true) {
			/*
			* If we press SDL_QUIT (Exit button), the game stops and closes
			*/
			//if (!inputManager->handleInput()) {
			//	break;
			//}

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

		delete ogreManager;
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
};