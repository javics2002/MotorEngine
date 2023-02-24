#include "Ogre.h"
#include "OgreWindow.h"
#include <OgreRoot.h>
#include <iostream>

void me::initOgre(const char* windowName)
{
	OgreWindow* ogre = new OgreWindow(windowName);
	ogre->init();

	ogre->getRoot()->startRendering();
	// mRoot = ogre->getRoot();
}
