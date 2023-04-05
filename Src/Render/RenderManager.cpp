#include "RenderManager.h"
#include "Utils/Vector3.h"
#include "Utils/Vector4.h"

#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreQuaternion.h>
#include <OgreEntity.h>
#include <OgreLight.h>
#include <OgreFileSystemLayer.h>
#include <OgreConfigFile.h>
#include <OgreShaderGenerator.h>
#include <OgreRTShaderSystem.h>
#include <OgreMaterialManager.h>
#include <OgreColourValue.h>
#include <OgreVector.h>
#include <iostream>
#include "OgreTextAreaOverlayElement.h"
#include "Render/RenderWindow.h"
#include "Render/RenderCamera.h"
#include "Render/RenderMesh.h"
#include "Render/RenderParticleSystem.h"
#include "Render/SGTechniqueResolverListener.h"

// Animation includes
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

using namespace me;

RenderManager::RenderManager()
{
	initRoot();
	initWindow();
	locateResources();
	loadResources();
	initialiseRTShaderSystem();
	mSM = mRoot->createSceneManager();
	mShaderGenerator->addSceneManager(mSM);
}

void RenderManager::initRoot()
{
	mFSLayer = new Ogre::FileSystemLayer("OgreFileSystem");

	mPluginCfgPath = mFSLayer->getConfigFilePath("plugins.cfg");
	mOgreCfgPath = mFSLayer->getConfigFilePath("ogre.cfg");

	if (!Ogre::FileSystemLayer::fileExists(mPluginCfgPath))
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "OgreManager::initRoot");
	if (!Ogre::FileSystemLayer::fileExists(mOgreCfgPath))
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "ogre.cfg", "OgreManager::initRoot");
	

	mSolutionPath = mFSLayer->getConfigFilePath("plugins.cfg");   // A�adido para definir directorios relativos al de la soluci�n 

	mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);
	mFSLayer->setHomePath(mSolutionPath);   // Para los archivos de configuraci�n ogre. (en el bin de la solubi�n)
	//mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);   // Quito /bin

	std:: string logPath = mFSLayer->getWritablePath("ogre.log");
	mRoot = new Ogre::Root(mPluginCfgPath, mOgreCfgPath, mFSLayer->getWritablePath("ogre.log"));

	if (!mRoot)
		OGRE_EXCEPT(Ogre::Exception::ERR_INVALID_CALL, "Ogre::Root", "OgreManager::initRoot");
	mRoot->restoreConfig();
}

void RenderManager::shutdown()
{
	// Destroy the RT Shader System.
	destroyRTShaderSystem();
	delete mFSLayer;
	delete mOgreWindow;
}

void RenderManager::initWindow()
{
	mOgreWindow = new RenderWindow("OgreWindow");
	mOgreWindow->init(mRoot);
}

void RenderManager::locateResources()
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
		const Ogre::ConfigFile::SettingsMultiMap&settings = seci->second;
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

void RenderManager::loadResources() {
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

bool RenderManager::initialiseRTShaderSystem() {
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

void RenderManager::destroyRTShaderSystem()
{
	// Restore default scheme.
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	// Unregister the material manager listener.
	if (mMaterialMgrListener != nullptr)
	{
		Ogre::MaterialManager::getSingleton().removeListener(mMaterialMgrListener);
		delete mMaterialMgrListener;
		mMaterialMgrListener = nullptr;
	}

	// Destroy RTShader system.
	if (mShaderGenerator != nullptr)
	{
		Ogre::RTShader::ShaderGenerator::destroy();
		mShaderGenerator = nullptr;
	}
}

RenderMesh* RenderManager::getMesh(std::string name)
{
	if (!mMeshes.count(name))
		return nullptr;

	return mMeshes[name];
}
RenderCamera* RenderManager::getCamera(std::string name)
{

	if (!mCameras.count(name))
		return nullptr;

	return mCameras[name];
}

RenderParticleSystem* RenderManager::getParticle(std::string name)
{
	if (!mParticles.count(name))
		return nullptr;

	return mParticles[name];
}

me::RenderManager::~RenderManager()
{
	for (auto& it : mCameras) {

		delete it.second;
	}
	mCameras.clear();

	for (auto& it2 : mMeshes) {

		delete it2.second;
	}
	mMeshes.clear();

	for (auto& it3 : mLights) {
		Ogre::SceneNode* node = it3.second->getParentSceneNode();
		node->detachAllObjects();
		mSM->destroyLight(it3.second);
		mSM->destroySceneNode(node);
	}
	mLights.clear();

	/*if (mRoot != nullptr)
	{
		mRoot->saveConfig();
	}*/

	shutdown();
	delete mRoot;
	mRoot = nullptr;
}

bool RenderManager::createCamera(std::string name, std::string parentName, int nearDist, 
	int farDist, bool autoRatio, int zOrder, Vector4 colour)
{
	if (mCameras.count(name))
		return false;

	RenderCamera* camera = new RenderCamera();
	Ogre::SceneNode* cameraNode = createChildNode(name, parentName);
	
	camera->init(cameraNode, mSM, mOgreWindow->getRenderWindow());
	camera->createCamera(name.c_str(), nearDist, farDist, autoRatio, zOrder, colour.v4toOgreColourValue());

	mCameras[name] = camera;

	return true;
}

bool RenderManager::createCamera(std::string name, float nearDist, float farDist, bool autoRatio, 
	int zOrder, Vector4 colour)
{
	if (mCameras.count(name))
		return false;

	RenderCamera* camera = new RenderCamera();
	Ogre::SceneNode* cameraNode = createNode(name);

	camera->init(cameraNode, mSM, mOgreWindow->getRenderWindow());
	camera->createCamera(name.c_str(), nearDist, farDist, autoRatio, zOrder, colour.v4toOgreColourValue());

	mCameras[name] = camera;

	return true;
}

bool RenderManager::setCameraInfo(std::string name, const Vector3& pos, const Vector3& look)
{
	RenderCamera* cam = getCamera(name);
	if (cam == nullptr)
		return false;

	cam->setPosition(pos);
	cam->lookAt(look);

	return true;
}


bool RenderManager::setViewportDimension(std::string name, float left, float top, float width, float height)
{
	RenderCamera* cam = getCamera(name);
	if (cam == nullptr)
		return false;

	cam->setViewportDimension(left, top, width, height);

	return true;
}


void RenderManager::destroyCamera(std::string name)
{
	RenderCamera* cam = getCamera(name);
	if (cam == nullptr)
	{
		std::cout << "Try to destroy nullptr camera with this name " << name << std::endl;
	}
	else
	{
		delete cam;
		mCameras.erase(name);
	}

}

void RenderManager::createNewLight(std::string name, const Vector3& pos, const Vector3& dir)
{
	Ogre::Light* light = mSM->createLight(name);
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setVisible(true);
	Ogre::SceneNode* lightNode = createNode(name);
	lightNode->attachObject(light);
	lightNode->setDirection(dir.v3ToOgreV3());
	lightNode->setPosition(pos.v3ToOgreV3());
	mLights[name] = light;
}

bool RenderManager::createMesh(std::string name, std::string nameMesh)
{
	if (mMeshes.count(name))
		return false;

	Ogre::SceneNode* entityNode = createNode(name);
	RenderMesh* mesh = new RenderMesh(entityNode, nameMesh);


	mMeshes[name] = mesh;

	return true;
}

bool RenderManager::setMeshPosition(std::string name, Vector3 pos)
{
	RenderMesh* mesh = getMesh(name);
	if (mesh == nullptr)
		return false;

	mesh->setPosition(pos.v3ToOgreV3());

	return true;
}

bool RenderManager::setMeshScale(std::string name, Vector3 scale)
{
	RenderMesh* mesh = getMesh(name);
	if (mesh == nullptr)
		return false;

	mesh->setScale(scale.v3ToOgreV3());
	
	return true;
}

bool RenderManager::setMeshRotation(std::string name, Vector4 rot)
{
	RenderMesh* mesh = getMesh(name);
	if (mesh == nullptr)
		return false;

	mesh->setRotation(rot.v4ToOgreQuaternion());

	return true;
}

bool RenderManager::setMeshMaterial(std::string name, std::string nameMaterial)
{
	RenderMesh* mesh = getMesh(name);
	if (mesh == nullptr)
		return false;

	mesh->setMaterial(nameMaterial);

	return true;
}

void RenderManager::destroyMesh(std::string name)
{
	RenderMesh* mesh = getMesh(name);
	if (mesh == nullptr)
	{
		std::cout << "Try to destroy nullptr mesh with this name " << name << std::endl;
	}
	else
	{
		delete mesh;
		mMeshes.erase(name);
	}

}

bool RenderManager::setMeshTransform(std::string name, Vector3 pos, Vector3 scale)
{
	RenderMesh* mesh = getMesh(name);
	if (mesh == nullptr)
		return false;

	mesh->setTransform(pos.v3ToOgreV3(), scale.v3ToOgreV3(), Ogre::Quaternion::IDENTITY);

	return true;
}

bool RenderManager::setMeshTransform(std::string name,  Vector3 pos, Vector3 scale, Vector4 rot)
{
	RenderMesh* mesh = getMesh(name);
	if (mesh == nullptr)
		return false;
	
	mesh->setTransform(pos.v3ToOgreV3(), scale.v3ToOgreV3(), rot.v4ToOgreQuaternion());

	return true;
}



bool RenderManager::createParticle(std::string name, std::string nameParticle)
{
	if (mParticles.count(name))
		return false;

	Ogre::SceneNode* entityNode = createNode(name);
	RenderParticleSystem* particle = new RenderParticleSystem(name, entityNode, nameParticle);

	mParticles[name] = particle;

	return true;
}

bool RenderManager::setParticleTransform(std::string name, Vector3 pos, Vector3 scale)
{
	RenderParticleSystem* particle = getParticle(name);
	if (particle == nullptr)
		return false;

	particle->setTransform(pos.v3ToOgreV3(), scale.v3ToOgreV3(), Ogre::Quaternion::IDENTITY);

	return true;
}

bool RenderManager::setParticleTransform(std::string name, Vector3 pos, Vector3 scale, Vector4 rot)
{
	RenderParticleSystem* particle = getParticle(name);
	if (particle == nullptr)
		return false;

	particle->setTransform(pos.v3ToOgreV3(), scale.v3ToOgreV3(), rot.v4ToOgreQuaternion());

	return true;
}

bool RenderManager::setParticlePosition(std::string name, Vector3 pos)
{
	RenderParticleSystem* particle = getParticle(name);
	if (particle == nullptr)
		return false;

	particle->setPosition(pos.v3ToOgreV3());

	return true;
}

bool RenderManager::setParticleScale(std::string name, Vector3 scale)
{
	RenderParticleSystem* particle = getParticle(name);
	if (particle == nullptr)
		return false;

	particle->setScale(scale.v3ToOgreV3());

	return true;
}

bool RenderManager::setParticleRotation(std::string name, Vector4 rot)
{
	RenderParticleSystem* particle = getParticle(name);
	if (particle == nullptr)
		return false;

	particle->setRotation(rot.v4ToOgreQuaternion());

	return true;
}

bool RenderManager::setParticleEmitting(std::string name, bool emitted)
{
	RenderParticleSystem* particle = getParticle(name);
	if (particle == nullptr)
		return false;

	particle->setEmitting(emitted);

	return true;
}



Ogre::SceneNode* RenderManager::createNode(std::string name)
{
	return  mSM->getRootSceneNode()->createChildSceneNode(name);
}

Ogre::SceneNode* RenderManager::createChildNode(std::string name, std::string parent)
{
	return mSM->getSceneNode(parent)->createChildSceneNode(name);
}

Ogre::SceneNode* RenderManager::getRootSceneNode()
{
	return mSM->getRootSceneNode();
}

void RenderManager::render()
{
	mRoot->renderOneFrame();
}

RenderWindow* RenderManager::getOgreWindow()
{
	return mOgreWindow;
}

Ogre::Entity* RenderManager::getOgreEntity(std::string name)
{
	return getMesh(name)->getOgreEntity();
}

Ogre::TextAreaOverlayElement* RenderManager::createOverlayElement()
{
	//TODO
	return nullptr;
}

Ogre::SceneManager* RenderManager::getSceneManager()
{
	return mSM;
}