#ifdef _DEBUG
#pragma once
#ifndef __BULLET_MAIN
#define __BULLET_MAIN

#include <iostream>
#include <SDL3/SDL_events.h>

#include "PhysicsManager.h"
#include "Utils/Vector3.h"
#include "Ogre/OgreManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/RigidBody.h"
#include "EntityComponent/MeshRenderer.h"
#include "EntityComponent/Collider.h"

using namespace me;

int main() {
    
    pm().start();

    std::string cam = "CameraDemo";

    om().createCamera(cam, 5, 10000, true, 0, Ogre::ColourValue(0, 0, 0.5));
    om().setCameraInfo(cam, Ogre::Vector3f(0, 300, 600), Ogre::Vector3f(0, -1, 0.25));

    Entity* plane = new Entity("plane");    

    auto tr = plane->addComponent<Transform>("transform");
    tr->setScale(Vector3(5, 0.1, 5));

    plane->addComponent<RigidBody>("rigidBody", 1, 1, 5, 0.3, 0.5, false);
    plane->addComponent<MeshRenderer>("meshRenderer",  "p", "cube.mesh")->setMaterial("Material/roja");

    Entity* cube = new Entity("cube");

    cube->addComponent<Transform>("transform")->setPosition(Vector3(0, 200, 0));

    cube->addComponent<RigidBody>("rigidBody", 1, 0, 5, 0.3, 0.5, false);
    cube->addComponent<MeshRenderer>("meshRenderer", "c", "cube.mesh")->setMaterial("Material/marronclaro");


    om().createNewLight("Luz", Vector3(0, 500, 500).v3ToOgreV3(), Vector3(0, -1, -1).v3ToOgreV3());

    //Transform *tr = cube->getComponent<Transform>("transform");
    //int degrees = 0;
    //tr->rotate(degrees, AXIS_ROTATIONS_Z);
    //degrees += 1;

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {

        om().render();

        plane->update();
        cube->update();

        pm().update(0.01667);

        switch (event.type) {
        case SDL_EVENT_QUIT:
            return 0;
        }
    }

    return 0;
}

#endif
#endif