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
    
    pm();

    std::string cam = "CameraDemo";

    om().createCamera(cam, 5, 10000, true, 0, Ogre::ColourValue(0, 0, 0.5));
    om().setCameraInfo(cam, Ogre::Vector3f(0, 300, 500), Ogre::Vector3f(0, -1, -1));

    Entity* cube = new Entity("cube");    

    cube->addComponent<Transform>("transform");
    cube->getComponent<Transform>("transform")->setScale(Vector3(5, 0.1, 5));
    //Ogre::Quaternion quat(Ogre::Degree(80), Ogre::Vector3::UNIT_X);
    //cube->getComponent<Transform>("transform")->setRotation(quat);


    cube->addComponent<RigidBody>("rigidBody", 1, 0, 5, 0.3, 0.5, false);
    cube->addComponent<MeshRenderer>("meshRenderer",  "c", "cube.mesh");

    om().createNewLight("Luz", Vector3(0, 500, 500).v3ToOgreV3(), Vector3(0, -1, -1).v3ToOgreV3());

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {

        om().render();

        cube->update();

        switch (event.type) {
        case SDL_EVENT_QUIT:
            return 0;
        }
    }

    return 0;
}

#endif
#endif