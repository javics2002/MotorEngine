#ifdef _DEBUG
#pragma once
#ifndef __BULLET_MAIN
#define __BULLET_MAIN

#include <fstream>
#include <iostream>
#include <SDL3/SDL_events.h>
#include <string>
#include <map>

#include "PhysicsManager.h"
#include "Utils/Vector3.h"
#include "Input/InputManager.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Components/RigidBody.h"
#include "EntityComponent/Components/MeshRenderer.h"
#include "EntityComponent/Components/Collider.h"
#include "EntityComponent/Components/FactoryComponent.h"

#include "EntityComponent/SceneManager.h"

using namespace me;

int main() {

	physicsManager().start();

	std::string cam = "CameraDemo";

	renderManager().createCamera(cam, 5, 10000, true, 0, Ogre::ColourValue(0, 0, 0.5));
	renderManager().setCameraInfo(cam, Ogre::Vector3f(0, 300, 600), Ogre::Vector3f(0, -1, 0.25));

	me::Entity* plane = new me::Entity("plane");

	plane->addComponent<Transform>("transform");
	

	/*auto trPlane = plane->addComponent<Transform>("transform");
	trPlane->setScale(Vector3(5, 0.1, 5));

	auto planeRb = plane->addComponent<RigidBody>("rigidBody", 1, 1, 5, 0.3, 0.5, false);
	plane->addComponent<MeshRenderer>("meshRenderer", "p", "cube.mesh")->setMaterial("Material/roja");
	plane->addComponent<Collider>("collider");

	me::Entity* cube = new me::Entity("cube");

	auto trCube = cube->addComponent<Transform>("transform");
	trCube->setPosition(Vector3(0, 200, 0));

	cube->addComponent<RigidBody>("rigidBody", 1, 0, 5, 0.3, 0.5, false);
	cube->addComponent<MeshRenderer>("meshRenderer", "c", "cube.mesh")->setMaterial("Material/marronclaro");
	cube->addComponent<Collider>("collider");*/

	renderManager().createNewLight("Luz", Vector3(0, 500, 500).v3ToOgreV3(), Vector3(0, -1, -1).v3ToOgreV3());

	SDL_Event event;
	bool quit = false;

	while (!quit) {

		while (SDL_PollEvent(&event)) {

		}

		//plane->update();
		//cube->update();

		renderManager().render();
		physicsManager().update(0.01667);

		switch (event.type) {
		case SDL_EVENT_QUIT:
			return quit = true;
		}
	}

	return 0;

}


#endif
#endif