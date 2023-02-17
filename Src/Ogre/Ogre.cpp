#include "Ogre.h"
#include <OgreRoot.h>
#include <iostream>


void saluda(const char* name) {
	Ogre::Root* root;
	root = new Ogre::Root();
	std::cout << "Ogre cargando Correctamente: " << name << std::endl;
}
//
//void init()
//{
//	createRoot()
//}
