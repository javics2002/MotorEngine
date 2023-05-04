#ifdef _DEBUG
#pragma once
#ifndef __OGRE_MAIN
#define __OGRE_MAIN


#include <iostream>
#include <string>
#include "RenderManager.h"
#include <OgreVector.h>
#include "Utils/checkML.h"



using namespace me;



int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	RenderManager* ogreMgr = RenderManager::Instance();
	std::string camJ1 = "CameraJugador1";
	std::string cubo = "Cubo";
	ogreMgr->createMesh(cubo, "cube.mesh");
	ogreMgr->setMeshMaterial(cubo, "Material/roja");
	
	ogreMgr->render();
	
	
	return 0;
}

#endif
#endif