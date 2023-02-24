#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"
#include "OgreViewport.h"
#include "OgreLight.h"
#include <string>


me::OgreCamera::OgreCamera()
{
	mCamera = nullptr;
	mViewport = nullptr;
	mCameraNode = nullptr;
	mLightNode = nullptr;
	mSceneMgr = nullptr;
	mRenderWindow = nullptr;
}

void me::OgreCamera::init(Ogre::SceneNode* CameraNode, Ogre::SceneManager* SceneMgr, Ogre::RenderWindow* RenderWindow)
{
	mSceneMgr = SceneMgr;
	mCameraNode= CameraNode;
	mRenderWindow = RenderWindow;
}

void me::OgreCamera::createCamera(const char* name, int nearDist, int farDist, bool autoRadio)
{
	mCamera = mSceneMgr->createCamera(name);
	mCamera->setNearClipDistance(nearDist);
	mCamera->setFarClipDistance(farDist);
	mCamera->setAutoAspectRatio(autoRadio);
	mCameraNode->attachObject(mCamera);

	Ogre::Light* luz = mSceneMgr->createLight("Luz");
	luz->setType(Ogre::Light::LT_POINT);
	luz->setVisible(true);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(20, 80, 50));  //vec3.normalise();
	mLightNode->setPosition(0, -1000, 1000);
	
	
}

void me::OgreCamera::renderCamera()
{
	mViewport = mRenderWindow->addViewport(mCamera);
	mViewport->setBackgroundColour(Ogre::ColourValue(0.8f, 0.8f, 0.8f));
}

me::OgreCamera::~OgreCamera()
{

}


void me::OgreCamera::setPosition(int x, int y, int z)
{
	mCameraNode->setPosition(Ogre::Vector3(x, y, z));
}

void me::OgreCamera::lookAt(int x, int y, int z)
{
	mCameraNode->lookAt(Ogre::Vector3(x, y, z), Ogre::Node::TS_WORLD);
}

void me::OgreCamera::setViewportDimension(float left, float top, float width, float height)
{
	mViewport->setDimensions(left, top, width, height);
}



