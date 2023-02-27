#include "OgreManager.h"
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreLight.h>
#include <OgreFileSystemLayer.h>
#include <OgreConfigFile.h>
#include <OgreShaderGenerator.h>
#include <OgreRTShaderSystem.h>
#include <OgreMaterialManager.h>
#include <OgreMath.h>
#include <OgreMeshManager.h>
#include <iostream>

#include "Ogre/OgreWindow.h"
#include "Ogre/OgreCamera.h"
#include "Ogre/SGTechniqueResolverListener.h"

using namespace me;

OgreManager::OgreManager()
{
	initRoot();
	initWindow();
	locateResources();
	loadResources();
	initialiseRTShaderSystem();
	mSM = mRoot->createSceneManager();
	mShaderGenerator->addSceneManager(mSM);
}

void OgreManager::initRoot()
{
	mFSLayer = new Ogre::FileSystemLayer("OgreFileSystem");

	mPluginCfgPath = mFSLayer->getConfigFilePath("plugins.cfg");
	mOgreCfgPath = mFSLayer->getConfigFilePath("ogre.cfg");

	if (!Ogre::FileSystemLayer::fileExists(mPluginCfgPath))
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "OgreManager::initRoot");
	if (!Ogre::FileSystemLayer::fileExists(mOgreCfgPath))
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "ogre.cfg", "OgreManager::initRoot");
	

	mSolutionPath = mFSLayer->getConfigFilePath("plugins.cfg");   // Añadido para definir directorios relativos al de la solución 

	mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);
	mFSLayer->setHomePath(mSolutionPath);   // Para los archivos de configuración ogre. (en el bin de la solubión)
	//mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);   // Quito /bin

	mRoot = new Ogre::Root(mPluginCfgPath, mOgreCfgPath, mFSLayer->getWritablePath("ogre.log"));

	if (!mRoot)
		OGRE_EXCEPT(Ogre::Exception::ERR_INVALID_CALL, "Ogre::Root", "OgreManager::initRoot");
	mRoot->restoreConfig();


}

void me::OgreManager::initWindow()
{
	ogreWindow = new OgreWindow("OgreWindow");
	ogreWindow->init(mRoot);
}

bool OgreManager::initialiseRTShaderSystem() {
	if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
		// Core shader libs not found -> shader generating will fail.
		if (mRTShaderLibPath.empty())
			return false;

		// Create and register the material manager listener if it doesn't exist yet.
		if (!mMaterialMgrListener) {
			mMaterialMgrListener = new SGTechniqueResolverListener(mShaderGenerator);
			Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
		}
	}

	return true;
}



me::OgreManager::~OgreManager()
{
	delete ogreWindow;
}

bool me::OgreManager::createCamera(std::string name, std::string parentName, int nearDist, int farDist, bool autoRadio)
{

	if (mCameras.count(name))
		return false;

	OgreCamera* camera = new OgreCamera();
	Ogre::SceneNode* cameraNode = mSM->getSceneNode(parentName)->createChildSceneNode(name);
	
	camera->init(cameraNode, mSM, ogreWindow->getRenderWindow());

	camera->createCamera(name.c_str(), nearDist, farDist, autoRadio);

	mCameras[name] = camera;

	return true;
}

bool me::OgreManager::createCamera(std::string name, int nearDist, int farDist, bool autoRadio)
{
	if (mCameras.count(name))
		return false;

	OgreCamera* camera = new OgreCamera();
	Ogre::SceneNode* cameraNode =createNode(name);

	camera->init(cameraNode, mSM, ogreWindow->getRenderWindow());

	camera->createCamera(name.c_str(), nearDist, farDist, autoRadio);

	mCameras[name] = camera;

	return true;
}

void me::OgreManager::createNewLight(std::string name)
{
	
	Ogre::Light* light = mSM->createLight(name);
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setVisible(true);
	Ogre::SceneNode* lightNode = createNode(name);
	lightNode->attachObject(light);
	lightNode->setDirection(Ogre::Vector3(0,0,-1));
	lightNode->setPosition(20, 80, 5000);
	

}

OgreCamera* me::OgreManager::getCamera(std::string name)
{
	
	if (!mCameras.count(name))
		return nullptr;

	return mCameras[name];
}

bool me::OgreManager::setCameraInfo(std::string name, int x, int y, int z, int x1, int y1, int z1)
{
	OgreCamera* cam = getCamera(name);
	if (cam == nullptr)
		return false;

	cam->setPosition(x,y,z);
	cam->lookAt(x1,y1,z1);
	

	return true;

}

bool me::OgreManager::renderCamera(std::string name, float left, float top, float width, float height)
{
	OgreCamera* cam = getCamera(name);
	if (cam == nullptr)
		return false;

	cam->renderCamera();
	cam->setViewportDimension(left, top, width, height); //infractura en OgreMain.dll

	return true;
}

Ogre::SceneNode* me::OgreManager::createNode(std::string name)
{
	return  mSM->getRootSceneNode()->createChildSceneNode(name);
}

Ogre::SceneNode* me::OgreManager::createChildNode(std::string name, Ogre::SceneNode* parent)
{
	return parent->createChildSceneNode(name);
}



void OgreManager::loadResources() {
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}


void OgreManager::locateResources()
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

	//sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	//const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

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

	//Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void me::OgreManager::render()
{
	mRoot->renderOneFrame();
}

void me::OgreManager::scene1()
{
	Ogre::SceneNode* mSinbadNode;
	Ogre::Entity* ent;
	ent = mSM->createEntity("Sinbad.mesh");
	mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("Sinbad");
	mSinbadNode->attachObject(ent);
	mSinbadNode->setPosition(0, 0, 0);
	//mSinbadNode->setScale(10, 10, 10);
	//mSinbadNode->yaw(Ogre::Degree(-45));
	//mSinbadNode->showBoundingBox(true);
	mSinbadNode->setVisible(false);
	
}
