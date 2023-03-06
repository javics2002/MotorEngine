#include "OgreWindow.h"
#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_syswm.h>

#include "Window.h"


using namespace me;

OgreWindow::OgreWindow(const std::string windowName)
{
	mWindowName = windowName;
}

OgreWindow::~OgreWindow()
{

}

void OgreWindow::init(Ogre::Root* root)
{
	root->initialise(false, mWindowName);
	createWindow(root);
	//setWindowGrab(true);
}

Ogre::RenderWindow* me::OgreWindow::getRenderWindow()
{
	return mRenderWindow;
}

SDL_Window* me::OgreWindow::getSdlWindow()
{
	return mSdlWindow;
}



void OgreWindow::createWindow(Ogre::Root* root)
{
	uint32_t w, h;
	std::string x;
	Ogre::ConfigOptionMap cOptionMap = root->getRenderSystem()->getConfigOptions();
	std::istringstream mode(cOptionMap["Video Mode"].currentValue);
	mode >> w;
	mode >> x;
	mode >> h;

	Ogre::NameValuePairList miscParams;
	miscParams["FSAA"] = cOptionMap["FSAA"].currentValue;
	miscParams["vsync"] = cOptionMap["VSync"].currentValue;
	miscParams["gamma"] = cOptionMap["sRGB Gamma Conversion"].currentValue;

	

	Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_FOCUS;

	if (cOptionMap["Full Screen"].currentValue == "Yes")
		flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_INPUT_FOCUS;

	mSdlWindow = win().get();
	
	//mSdlWindow = SDL_CreateWindow(mWindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	SDL_SysWMinfo* wmInfo = new SDL_SysWMinfo();
	SDL_version version;
	SDL_GetVersion(&version);
	wmInfo->version= SDL_VERSIONNUM(version.major, version.minor, version.patch);
	SDL_GetWindowWMInfo(mSdlWindow, wmInfo,wmInfo->version);

	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo->info.win.window));
	mRenderWindow = root->createRenderWindow(mWindowName, w, h, false, &miscParams);

	SDL_ShowCursor();
	//SDL_HideCursor();

}


void OgreWindow::setWindowGrab(bool bGrab)
{
	SDL_bool grab = SDL_bool(bGrab);
	SDL_SetWindowGrab(mSdlWindow, grab);
	//SDL_SetRelativeMouseMode(grab);
	
	grab ? SDL_ShowCursor() : SDL_HideCursor();
}



