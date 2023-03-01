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

}

void OgreManager::loadResources() {
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

bool OgreManager::initialiseRTShaderSystem() {
	if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

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

bool me::OgreManager::createCamera(std::string name, std::string parentName, int nearDist, int farDist, bool autoRadio, int zOrder)
{

	if (mCameras.count(name))
		return false;

	OgreCamera* camera = new OgreCamera();
	Ogre::SceneNode* cameraNode = createChildNode(name, parentName);
	
	camera->init(cameraNode, mSM, ogreWindow->getRenderWindow());

	camera->createCamera(name.c_str(), nearDist, farDist, autoRadio,zOrder);

	mCameras[name] = camera;

	return true;
}

bool me::OgreManager::createCamera(std::string name, int nearDist, int farDist, bool autoRadio, int zOrder)
{
	if (mCameras.count(name))
		return false;

	OgreCamera* camera = new OgreCamera();
	Ogre::SceneNode* cameraNode =createNode(name);

	camera->init(cameraNode, mSM, ogreWindow->getRenderWindow());

	camera->createCamera(name.c_str(), nearDist, farDist, autoRadio,zOrder);

	mCameras[name] = camera;

	return true;
}

void me::OgreManager::createNewLight(std::string name, int posX, int posY, int posZ, int dirX, int dirY, int dirZ)
{
	
	Ogre::Light* light = mSM->createLight(name);
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setVisible(true);
	Ogre::SceneNode* lightNode = createNode(name);
	lightNode->attachObject(light);
	lightNode->setDirection(Ogre::Vector3(dirX, dirY, dirZ));
	lightNode->setPosition(posX,posY,posZ);
	

}

OgreCamera* me::OgreManager::getCamera(std::string name)
{
	
	if (!mCameras.count(name))
		return nullptr;

	return mCameras[name];
}

bool me::OgreManager::setCameraInfo(std::string name, int posX, int posY, int posZ, int lookX, int lookY, int lookZ)
{
	OgreCamera* cam = getCamera(name);
	if (cam == nullptr)
		return false;

	cam->setPosition(posX,posY,posZ);
	cam->lookAt(lookX,lookY,lookZ);
	

	return true;

}


bool me::OgreManager::setViewportDimension(std::string name, float left, float top, float width, float height)
{
	OgreCamera* cam = getCamera(name);
	if (cam == nullptr)
		return false;

	cam->setViewportDimension(left, top, width, height);


	return true;
}

Ogre::SceneNode* me::OgreManager::createNode(std::string name)
{
	return  mSM->getRootSceneNode()->createChildSceneNode(name);
}

Ogre::SceneNode* me::OgreManager::createChildNode(std::string name, std::string parent)
{
	return mSM->getSceneNode(parent)->createChildSceneNode(name);
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
	mSinbadNode->setScale(10, 10, 10);
	//mSinbadNode->yaw(Ogre::Degree(-45));
	//mSinbadNode->showBoundingBox(true);
	mSinbadNode->setVisible(true);
	
}
