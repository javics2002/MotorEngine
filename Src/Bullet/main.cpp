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

using namespace me;

int main() {
    
    pm();

    std::string cam = "CameraDemo";

    om().createCamera(cam, 5, 10000, true, 0, Ogre::ColourValue(0, 0, 0));
    om().setCameraInfo(cam, Ogre::Vector3f(0, 0, 500), Ogre::Vector3f(0, 0, -1));

    Entity* cube = new Entity("cube");    

    //cube->addComponent<Transform>();
    //cube->addComponent<RigidBody>(1, 1, 5, 0.3, 0.5, false);
    //cube->addComponent<MeshRenderer>("c", "cube.mesh");

    //Ogre::SceneNode* mCubeNode;
    

    
    //pm().update(5);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            return 0;
        }
    }

    return 0;
}

#endif
#endif