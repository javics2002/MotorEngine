#include "OgreWindow.h"
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreGpuProgramManager.h>
#include <OgreRenderWindow.h>
#include <OgreFileSystemLayer.h>
#include <iostream>
#include "SDL/Window.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_syswm.h>


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



void OgreWindow::setup() {

	mRoot->initialise(false, mWindowName);
	locateResources();
	initialiseRTShaderSystem(); // TODO: Esto que es?
	loadResources();

	createWindow();
	setWindowGrab(false);

	// mRoot->addFrameListener(this);
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

	

	Uint32 flags = SDL_WINDOW_RESIZABLE;

	if (cOptionMap["Full Screen"].currentValue == "Yes")  
		flags = SDL_WINDOW_FULLSCREEN;
	
	// mSdlWindow = win().create(mWindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);
	// win().init(mWindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	me::Window::init(SDL_INIT_EVERYTHING, "Juegox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 854, 480, SDL_WINDOW_INPUT_FOCUS);
	mRenderWindow = win().get();
	
	// mSdlWindow = SDL_CreateWindow(mWindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	SDL_SysWMinfo* wmInfo = new SDL_SysWMinfo();
	SDL_GetWindowWMInfo(mRenderWindow, wmInfo,wmInfo->version);

	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo->info.win.window));
	// mRenderWindow = mRoot->createRenderWindow(mWindowName, w, h, false, &miscParams);

	// SDL_ShowCursor();
	//SDL_HideCursor();

}

Ogre::Root* OgreWindow::getRoot() {
	return mRoot;
}

void OgreWindow::setWindowGrab(bool bGrab)
{
	SDL_bool grab = SDL_bool(bGrab);
	SDL_SetWindowGrab(mRenderWindow, grab);
	//SDL_SetRelativeMouseMode(grab);
	
	grab ? SDL_ShowCursor() : SDL_HideCursor();
}



