#include "OgreWindow.h"
#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreFileSystemLayer.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include <iostream>

using namespace me;

OgreWindow::OgreWindow(const std::string windowName)
{
	mWindowName = windowName;
	mRoot = nullptr;
	mFirstRun = true;

	//mShaderGenerator = nullptr;
	//mMaterialMgrListener = nullptr;


}

OgreWindow::~OgreWindow()
{

}

void OgreWindow::init()
{
	initRoot();

	setup();
	// mOverlaySystem = new Ogre::OverlaySystem();
}

void OgreWindow::initRoot()
{

	Ogre::FileSystemLayer* fsl = new Ogre::FileSystemLayer(mWindowName);
	
	mPluginCfgPath = fsl->getConfigFilePath("plugins.cfg");
	mOgreCfgPath = fsl->getConfigFilePath("ogre.cfg");
	mOgreLogPath = fsl->getConfigFilePath("Ogre.log");

	delete fsl;
	if (!Ogre::FileSystemLayer::fileExists(mPluginCfgPath))
	{	
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "OgreWindow::initRoot");
	}

	if (!Ogre::FileSystemLayer::fileExists(mOgreCfgPath))
	{	
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "ogre.cfg", "OgreWindow::initRoot");
	}

	if (!Ogre::FileSystemLayer::fileExists(mOgreLogPath))
	{	
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "Ogre.log", "OgreWindow::initRoot");
	}


	mRoot = new Ogre::Root(mPluginCfgPath, mOgreCfgPath, mOgreLogPath);

	if(!mRoot)
		OGRE_EXCEPT(Ogre::Exception::ERR_INVALID_CALL, "Ogre::Root", "OgreWindow::initRoot");
	mRoot->restoreConfig();

}



void OgreWindow::setup() {

	mRoot->initialise(false, mWindowName);
	createWindow();
	
}

void OgreWindow::createWindow()
{
	uint32_t w, h;
	std::string x;
	Ogre::ConfigOptionMap cOptionMap = mRoot->getRenderSystem()->getConfigOptions();
	std::istringstream mode(cOptionMap["Video Mode"].currentValue);
	mode >> w;
	mode >> x;
	mode >> h;

	Ogre::NameValuePairList miscParams;
	miscParams["FSAA"] = cOptionMap["FSAA"].currentValue;
	miscParams["vsync"] = cOptionMap["VSync"].currentValue;
	miscParams["gamma"] = cOptionMap["sRGB Gamma Conversion"].currentValue;

	if (!SDL_WasInit(SDL_INIT_VIDEO)) 
		SDL_InitSubSystem(SDL_INIT_VIDEO);

	Uint32 flags = SDL_WINDOW_RESIZABLE;

	if (cOptionMap["Full Screen"].currentValue == "Yes")  
		flags = SDL_WINDOW_FULLSCREEN;

	mSdlWindow = SDL_CreateWindow(mWindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(mSdlWindow, &wmInfo);

	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));
	mRenderWindow = mRoot->createRenderWindow(mWindowName, w, h, false, &miscParams);

	SDL_ShowCursor(true);

}
