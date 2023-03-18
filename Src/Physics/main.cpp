#ifdef _DEBUG
#pragma once
#ifndef __BULLET_MAIN
#define __BULLET_MAIN

#include <fstream>
#include <iostream>
#include <SDL3/SDL_events.h>
#include <json.hpp>

#include "PhysicsManager.h"
#include "Utils/Vector3.h"
#include "Input/InputManager.h"
#include "Render/OgreManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/RigidBody.h"
#include "EntityComponent/MeshRenderer.h"
#include "EntityComponent/Collider.h"

using namespace me;

using json = nlohmann::json;

int main() {
    
    pm().start();

    std::string cam = "CameraDemo";

    om().createCamera(cam, 5, 10000, true, 0, Ogre::ColourValue(0, 0, 0.5));
    om().setCameraInfo(cam, Ogre::Vector3f(0, 300, 600), Ogre::Vector3f(0, -1, 0.25));

    Entity* plane = new Entity("plane");    

    auto trPlane = plane->addComponent<Transform>("transform");
    trPlane->setScale(Vector3(5, 0.1, 5));

    auto planeRb =  plane->addComponent<RigidBody>("rigidBody", 1, 1, 5, 0.3, 0.5, false);
    plane->addComponent<MeshRenderer>("meshRenderer",  "p", "cube.mesh")->setMaterial("Material/roja");
    plane->addComponent<Collider>("collider");

    Entity* cube = new Entity("cube");

    auto trCube = cube->addComponent<Transform>("transform");
    trCube->setPosition(Vector3(0, 200, 0));

    cube->addComponent<RigidBody>("rigidBody", 1, 0, 5, 0.3, 0.5, false);
    cube->addComponent<MeshRenderer>("meshRenderer", "c", "cube.mesh")->setMaterial("Material/marronclaro");
    cube->addComponent<Collider>("collider");

    om().createNewLight("Luz", Vector3(0, 500, 500).v3ToOgreV3(), Vector3(0, -1, -1).v3ToOgreV3());

    SDL_Event event;
    bool quit = false;

    std::fstream file;

    file.open("ejemplo.json");

    json info;

    info.parse(file);

    std::cout << "x: " << info["x"] << "\n";
    std::cout << "y: " << info["y"] << "\n";
    std::cout << "z: " << info["z"] << "\n";

    file.close();

    while (!quit) {

        while (SDL_PollEvent(&event)) {

        }

        plane->update();
        cube->update();

        om().render();
        pm().update(0.01667);

        switch (event.type) {
        case SDL_EVENT_QUIT:
            return quit = true;
        }
    }

    return 0;
}

#endif
#endif