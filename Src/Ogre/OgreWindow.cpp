#include "OgreWindow.h"
#include <OgreRoot.h>
#include <OgreFileSystemLayer.h>
// #include <SDL.h>

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

bool OgreWindow::init()
{
	mPluginCfgPath = "./plugins.cfg";
	mOgreCfgPath = "./ogre.cfg";
	mOgreLogPath = "./Ogre.log";

	if (!Ogre::FileSystemLayer::fileExists(mPluginCfgPath))
	{	// IG2: OGRE_CONFIG_DIR tiene un valor absoluto no portable
		//pluginsPath = Ogre::FileSystemLayer::resolveBundlePath(OGRE_CONFIG_DIR "/plugins" OGRE_BUILD_SUFFIX ".cfg");
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "IG2ApplicationContext::createRoot");
	}

	if (!Ogre::FileSystemLayer::fileExists(mOgreCfgPath))
	{	// IG2: OGRE_CONFIG_DIR tiene un valor absoluto no portable
		//pluginsPath = Ogre::FileSystemLayer::resolveBundlePath(OGRE_CONFIG_DIR "/plugins" OGRE_BUILD_SUFFIX ".cfg");
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "ogre.cfg", "IG2ApplicationContext::createRoot");
	}

	if (!Ogre::FileSystemLayer::fileExists(mOgreLogPath))
	{	// IG2: OGRE_CONFIG_DIR tiene un valor absoluto no portable
		//pluginsPath = Ogre::FileSystemLayer::resolveBundlePath(OGRE_CONFIG_DIR "/plugins" OGRE_BUILD_SUFFIX ".cfg");
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "Ogre.log", "IG2ApplicationContext::createRoot");
	}


	mRoot = new Ogre::Root(mPluginCfgPath, mOgreCfgPath, mOgreLogPath);

	if(!mRoot)
		OGRE_EXCEPT(Ogre::Exception::ERR_INVALID_CALL, "Ogre::Root", "IG2ApplicationContext::createRoot");

	return mRoot->restoreConfig();

	// mOverlaySystem = new Ogre::OverlaySystem();
}

void OgreWindow::setup() {

	/*int sdlInit = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	assert(SDL_GetError(), sdlInit != 0);*/

	// SDL_JoystickEventState(SDL_ENABLE);
	// SDL_JoystickUpdate();

	// mRoot->restoreConfig();
}