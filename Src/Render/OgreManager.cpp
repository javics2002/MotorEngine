#include "OgreManager.h"
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
#include "Render/OgreWindow.h"
#include "Render/OgreCamera.h"
#include "Render/OgreMesh.h"
#include "Render/OgreParticleSystem.h"
#include "Render/SGTechniqueResolverListener.h"

// Animation includes
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

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

void me::OgreManager::initWindow()
{
	mOgreWindow = new OgreWindow("OgreWindow");
	mOgreWindow->init(mRoot);
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

OgreMesh* me::OgreManager::getMesh(std::string name)
{
	if (!mMeshes.count(name))
		return nullptr;

	return mMeshes[name];
}
OgreCamera* me::OgreManager::getCamera(std::string name)
{

	if (!mCameras.count(name))
		return nullptr;

	return mCameras[name];
}

OgreParticleSystem* me::OgreManager::getParticle(std::string name)
{
	if (!mParticles.count(name))
		return nullptr;

	return mParticles[name];
}

me::OgreManager::~OgreManager()
{
	for (auto& it : mCameras) {

		delete it.second;
	}
	mCameras.clear();

	for (auto& it2 : mMeshes) {

		delete it2.second;
	}
	mMeshes.clear();
	delete mOgreWindow;
}

bool me::OgreManager::createCamera(std::string name, std::string parentName, int nearDist, int farDist, bool autoRadio, int zOrder, Ogre::ColourValue color)
{

	if (mCameras.count(name))
		return false;

	OgreCamera* camera = new OgreCamera();
	Ogre::SceneNode* cameraNode = createChildNode(name, parentName);
	
	camera->init(cameraNode, mSM, mOgreWindow->getRenderWindow());

	camera->createCamera(name.c_str(), nearDist, farDist, autoRadio,zOrder, color);

	mCameras[name] = camera;

	return true;
}

bool me::OgreManager::createCamera(std::string name, int nearDist, int farDist, bool autoRadio, int zOrder, Ogre::ColourValue color )
{
	if (mCameras.count(name))
		return false;

	OgreCamera* camera = new OgreCamera();
	Ogre::SceneNode* cameraNode = createNode(name);

	camera->init(cameraNode, mSM, mOgreWindow->getRenderWindow());

	camera->createCamera(name.c_str(), nearDist, farDist, autoRadio,zOrder, color);

	mCameras[name] = camera;

	return true;
}

bool me::OgreManager::setCameraInfo(std::string name, const Ogre::Vector3f &pos, const Ogre::Vector3f &look)
{
	OgreCamera* cam = getCamera(name);
	if (cam == nullptr)
		return false;

	cam->setPosition(pos);
	cam->lookAt(look);


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


void me::OgreManager::destroyCamera(std::string name)
{
	OgreCamera* cam = getCamera(name);
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

void me::OgreManager::createNewLight(std::string name, const Ogre::Vector3f &pos, const Ogre::Vector3f &dir)
{
	
	Ogre::Light* light = mSM->createLight(name);
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setVisible(true);
	Ogre::SceneNode* lightNode = createNode(name);
	lightNode->attachObject(light);
	lightNode->setDirection(dir);
	lightNode->setPosition(pos);
	

}

bool me::OgreManager::createMesh(std::string name, std::string nameMesh)
{

	if (mMeshes.count(name))
		return false;

	Ogre::SceneNode* entityNode = createNode(name);
	OgreMesh* mesh = new OgreMesh(entityNode, nameMesh);


	mMeshes[name] = mesh;

	return true;
}

bool me::OgreManager::setMeshPosition(std::string name, const Ogre::Vector3f &pos)
{
	OgreMesh* mesh = getMesh(name);
	if (mesh == nullptr)
		return false;

	mesh->setPosition( pos);

	return true;
}

bool me::OgreManager::setMeshScale(std::string name, const Ogre::Vector3f &scale)
{
	OgreMesh* mesh = getMesh(name);
	if (mesh == nullptr)
		return false;

	mesh->setScale(scale);
	
	return true;
}

bool me::OgreManager::setMeshRotation(std::string name, Ogre::Quaternion rot)
{
	OgreMesh* mesh = getMesh(name);
	if (mesh == nullptr)
		return false;

	mesh->setRotation(rot);

	return true;
}

bool me::OgreManager::setMeshMaterial(std::string name, std::string nameMaterial)
{
	OgreMesh* mesh = getMesh(name);
	if (mesh == nullptr)
		return false;

	mesh->setMaterial(nameMaterial);

	return true;
}

void me::OgreManager::destroyMesh(std::string name)
{
	OgreMesh* mesh = getMesh(name);
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


bool me::OgreManager::setMeshTransform(std::string name, const Ogre::Vector3f &pos, const Ogre::Vector3f &scale)
{
	OgreMesh* mesh = getMesh(name);
	if (mesh == nullptr)
		return false;

	mesh->setTransform(pos, scale , Ogre::Quaternion::IDENTITY);

	return true;
}

bool me::OgreManager::setMeshTransform(std::string name, const Ogre::Vector3f &pos, const Ogre::Vector3f &scale, const Ogre::Quaternion&rot)
{
	OgreMesh* mesh = getMesh(name);
	if (mesh == nullptr)
		return false;

	mesh->setTransform(pos, scale, rot);

	return true;
}



bool me::OgreManager::createParticle(std::string name, std::string nameParticle)
{
	if (mParticles.count(name))
		return false;

	Ogre::SceneNode* entityNode = createNode(name);
	OgreParticleSystem* particle = new OgreParticleSystem(name, entityNode, nameParticle);

	mParticles[name] = particle;

	return true;
}

bool me::OgreManager::setParticleTransform(std::string name, const Ogre::Vector3f& pos, const Ogre::Vector3f& scale)
{
	OgreParticleSystem* particle = getParticle(name);
	if (particle == nullptr)
		return false;

	particle->setTransform(pos, scale, Ogre::Quaternion::IDENTITY);

	return true;
}

bool me::OgreManager::setParticleTransform(std::string name, const Ogre::Vector3f& pos, const Ogre::Vector3f& scale, const Ogre::Quaternion& rot)
{
	OgreParticleSystem* particle = getParticle(name);
	if (particle == nullptr)
		return false;

	particle->setTransform(pos, scale, rot);

	return true;
}

bool me::OgreManager::setParticlePosition(std::string name, const Ogre::Vector3f& pos)
{
	OgreParticleSystem* particle = getParticle(name);
	if (particle == nullptr)
		return false;

	particle->setPosition(pos);

	return true;
}

bool me::OgreManager::setParticleScale(std::string name, const Ogre::Vector3f& scale)
{
	OgreParticleSystem* particle = getParticle(name);
	if (particle == nullptr)
		return false;

	particle->setScale(scale);

	return true;
}

bool me::OgreManager::setParticleRotation(std::string name, Ogre::Quaternion rot)
{
	OgreParticleSystem* particle = getParticle(name);
	if (particle == nullptr)
		return false;

	particle->setRotation(rot);

	return true;
}

bool me::OgreManager::setParticleEmitting(std::string name, bool emitted)
{
	OgreParticleSystem* particle = getParticle(name);
	if (particle == nullptr)
		return false;

	particle->setEmitting(emitted);

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

Ogre::SceneNode* me::OgreManager::getRootSceneNode()
{
	return mSM->getRootSceneNode();
}

void me::OgreManager::render()
{
	mRoot->renderOneFrame();
	//ogreAnimState->addTime(0.0166);
}

OgreWindow* me::OgreManager::getOgreWindow()
{
	return mOgreWindow;
}

Ogre::Entity* me::OgreManager::getOgreEntity(std::string name)
{
	return getMesh(name)->getOgreEntity();
}

Ogre::TextAreaOverlayElement* me::OgreManager::createOverlayElement()
{
	return nullptr;
}

Ogre::SceneManager* me::OgreManager::getSceneManager()
{
	return mSM;
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
	mSinbadNode->setVisible(true);

	// TEMPORAL ANIMATION
	Ogre::Real duration = 4;
	Ogre::Real step = duration / 4;

	Ogre::Animation* anim;
	anim = mSM->createAnimation("sinbadAnimation", duration);
	Ogre::NodeAnimationTrack* track = anim->createNodeTrack(0, mSinbadNode);
	anim->setInterpolationMode(Ogre::Animation::IM_LINEAR);

	Ogre::TransformKeyFrame* key;

	int counterStep = 0;

	key = track->createNodeKeyFrame(step * counterStep++);
	key->setRotation(Ogre::Quaternion());
	key->setScale(Ogre::Vector3(10));

	key = track->createNodeKeyFrame(step * counterStep++);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3::UNIT_X));
	key->setScale(Ogre::Vector3(10));

	key = track->createNodeKeyFrame(step * counterStep++);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-180), Ogre::Vector3::UNIT_X));
	key->setScale(Ogre::Vector3(10));

	key = track->createNodeKeyFrame(step * counterStep++);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-270), Ogre::Vector3::UNIT_X));
	key->setScale(Ogre::Vector3(10));

	key = track->createNodeKeyFrame(step * counterStep++);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-359), Ogre::Vector3::UNIT_X));
	key->setScale(Ogre::Vector3(10));

	ogreAnimState = mSM->createAnimationState("sinbadAnimation");
	ogreAnimState->setEnabled(true);
	ogreAnimState->setLoop(true);

	
}
