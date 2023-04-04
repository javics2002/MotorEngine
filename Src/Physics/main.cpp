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
#include "EntityComponent/Components/ComponentsFactory.h"

#include "EntityComponent/SceneManager.h"

#include "Utils/checkML.h"
using namespace me;

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	physicsManager().start();

	componentsFactory().addFactoryComponent("transform", new FactoryTransform());
	componentsFactory().addFactoryComponent("rigidbody", new FactoryRigidBody());
	//componentsFactory().addFactoryComponent("animator", new FactoryAnimator());
	componentsFactory().addFactoryComponent("meshrenderer", new FactoryMeshRenderer());
	componentsFactory().addFactoryComponent("collider", new FactoryCollider());

	std::string cam = "CameraDemo";

	renderManager().createCamera(cam, 5, 10000, true, 0, Ogre::ColourValue(0, 0, 0.5));
	renderManager().setCameraInfo(cam, Ogre::Vector3f(0, 300, 600), Ogre::Vector3f(0, -1, 0.25));

	me::Entity* plane = new me::Entity("plane");

	//plane->addComponent<Transform>("transform");
	

	auto trPlane = plane->addComponent<Transform>("transform");
	trPlane->setScale(Vector3(5, 0.1, 5));

	auto planeRb = plane->addComponent<RigidBody>("rigidbody");
	planeRb->setMass(5);
	planeRb->setRestitution(0.5f);
	planeRb->setFriction(0.3f);
	planeRb->setColShape(1);
	planeRb->setTrigger(false);
	planeRb->setMomeventType(2);
	auto planeMesh = plane->addComponent<MeshRenderer>("meshrenderer");
	planeMesh->init("p", "cube.mesh");
	planeMesh->setMaterial("Material/roja");
	plane->addComponent<Collider>("collider");

	me::Entity* cube = new me::Entity("cube");

	auto trCube = cube->addComponent<Transform>("transform");
	trCube->setPosition(Vector3(0, 200, 0));

	auto cubeRb =cube->addComponent<RigidBody>("rigidbody");
	cubeRb->setMass(5);
	cubeRb->setRestitution(0.5f);
	cubeRb->setFriction(0.3f);
	cubeRb->setColShape(0);
	cubeRb->setTrigger(false);
	cubeRb->setMomeventType(2);

	auto cubeMesh = cube->addComponent<MeshRenderer>("meshrenderer");
	cubeMesh->init("c", "cube.mesh");
	cubeMesh->setMaterial("Material/marronclaro");
	cube->addComponent<Collider>("collider");

	renderManager().createNewLight("Luz", Vector3(0, 500, 500).v3ToOgreV3(), Vector3(0, -1, -1).v3ToOgreV3());

	/*SDL_Event event;
	bool quit = false;

	while (!quit) {

		while (SDL_PollEvent(&event)) {

		}

		plane->update();
		cube->update();

		renderManager().render();
		physicsManager().update(0.01667);

		switch (event.type) {
		case SDL_EVENT_QUIT:
			return quit = true;
		}
	}*/

	plane->update();
	cube->update();

	renderManager().render();
	physicsManager().update(0.01667);

	delete plane;
	delete cube;
	return 0;

}


#endif
#endif