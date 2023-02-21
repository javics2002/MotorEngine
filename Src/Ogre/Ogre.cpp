#include "Ogre.h"
#include "OgreWindow.h"
#include <OgreRoot.h>
#include <iostream>

//void me::saluda(const char* name)
//{
//	Ogre::Root* root;
//	root = new Ogre::Root();
//	std::cout << "Ogre cargando Correctamente: " << name << std::endl;
//}

void me::initOgre(const char* windowName)
{
	OgreWindow* ogre = new OgreWindow(windowName);
	ogre->init();
}
