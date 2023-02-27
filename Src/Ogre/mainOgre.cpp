#ifdef _DEBUG
#pragma once
#ifndef __OGRE_MAIN
#define __OGRE_MAIN


#include <iostream>
#include <string>
#include "OgreManager.h"

using namespace me;



int main() {

	OgreManager* ogreMgr= OgreManager::instance();
	std::string camJ1 = "CameraJugador1";
	ogreMgr->createCamera(camJ1, 5,10000,true);
	ogreMgr->setCameraInfo(camJ1, 0, 0, 500, 0, 0, -1);
	ogreMgr->createNewLight("Luz");
	//ogreMgr->renderCamera(camJ1, 0.0f, 5.0f, 2.0f, 2.0f);
	ogreMgr->scene1();
	
	while (true)
	{
		ogreMgr->render();
	}
	
	int a;
	std::cin >> a;
	return 0;
}

#endif
#endif