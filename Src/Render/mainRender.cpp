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


	RenderManager* ogreMgr= RenderManager::instance();
	std::string camJ1 = "CameraJugador1";

	ogreMgr->createCamera(camJ1, 5,10000,true,0, Ogre::ColourValue(0, 0, 0));
	ogreMgr->setCameraInfo(camJ1,  Ogre::Vector3f( 0, 0, 500), Ogre::Vector3f( 0, 0, -1));

	//ogreMgr->setViewportDimension(camJ1, 0, 0, 0.3, 1);

	//std::string camJ2 = "CameraJugador2";
	//ogreMgr->createCamera(camJ2, 5, 10000, true,1, Ogre::ColourValue(0, 0, 0));
	//ogreMgr->setCameraInfo(camJ2,  Ogre::Vector3f(0, 300, 500),  Ogre::Vector3f( 0, 0, -1));

	//ogreMgr->setViewportDimension(camJ2, 0.5, 0, 0.3, 1);

	

	ogreMgr->createNewLight("Luz", Ogre::Vector3f(0, 500, 500),  Ogre::Vector3f(0, -1, -1));
	std::string cubo = "Cubo";
	ogreMgr->createMesh(cubo, "cube.mesh");
	ogreMgr->setMeshMaterial(cubo, "Material/roja");
	
	ogreMgr->render();
	
	
	return 0;
}

#endif
#endif