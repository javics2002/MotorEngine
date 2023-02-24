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

void OgreWindow::initRoot()
{
	mFSLayer = new Ogre::FileSystemLayer(mWindowName);
	
	mPluginCfgPath = mFSLayer->getConfigFilePath("plugins.cfg");
	mOgreCfgPath = mFSLayer->getConfigFilePath("ogre.cfg");
	mOgreLogPath = mFSLayer->getConfigFilePath("Ogre.log");

	if (!Ogre::FileSystemLayer::fileExists(mPluginCfgPath))
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "OgreWindow::initRoot");
	if (!Ogre::FileSystemLayer::fileExists(mOgreCfgPath))
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "ogre.cfg", "OgreWindow::initRoot");
	if (!Ogre::FileSystemLayer::fileExists(mOgreLogPath))
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "Ogre.log", "OgreWindow::initRoot");
	
	mSolutionPath = mPluginCfgPath;    // Añadido para definir directorios relativos al de la solución 

	mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);
	mFSLayer->setHomePath(mSolutionPath);   // Para los archivos de configuración ogre. (en el bin de la solubión)
	mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);   // Quito /bin

	mRoot = new Ogre::Root(mPluginCfgPath, mOgreCfgPath, mOgreLogPath);

	if(!mRoot)
		OGRE_EXCEPT(Ogre::Exception::ERR_INVALID_CALL, "Ogre::Root", "OgreWindow::initRoot");
	mRoot->restoreConfig();

}



void OgreWindow::setup() {

	mRoot->initialise(false, mWindowName);
	createWindow();

	setWindowGrab(false);
	locateResources();
	initialiseRTShaderSystem(); // TODO: Esto que es?
	loadResources();

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

bool OgreWindow::initialiseRTShaderSystem() {
	
	//if (Ogre::RTShader::ShaderGenerator::initialize())
	//{
	//	mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	//	// Core shader libs not found -> shader generating will fail.
	//	if (mRTShaderLibPath.empty())
	//		return false;
	//	// Create and register the material manager listener if it doesn't exist yet.
	//	if (!mMaterialMgrListener) {
	//		mMaterialMgrListener = new SGTechniqueResolverListener(mShaderGenerator);
	//		Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
	//	}
	//}

	return true;
}

void OgreWindow::loadResources() {
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}


void OgreWindow::locateResources()
{
	// load resource paths from config file
	Ogre::ConfigFile cf;

	Ogre::String resourcesPath = mFSLayer->getConfigFilePath("resources.cfg");
	if (Ogre::FileSystemLayer::fileExists(resourcesPath))
	{
		cf.load(resourcesPath);
	}
	else
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			Ogre::FileSystemLayer::resolveBundlePath(mSolutionPath + "\\media"),
			"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}

	Ogre::String sec, type, arch;
	// go through all specified resource groups
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// go through all resource paths
		for (i = settings.begin(); i != settings.end(); i++)
		{
			type = i->first;
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	// OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	// arch = genLocs.front().archive->getName();
	// type = genLocs.front().archive->getType();

	// Add locations for supported shader languages
	/*if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
		}

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
		}
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
	}*/

	/*mRTShaderLibPath = arch + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/materials", type, sec);

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/HLSL", type, sec);
	}*/

	
}


