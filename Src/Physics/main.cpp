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

	return 0;
}


#endif
#endif