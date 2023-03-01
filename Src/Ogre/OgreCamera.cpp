#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"
#include "OgreViewport.h"
#include <string>


me::OgreCamera::OgreCamera()
{
	mCamera = nullptr;
	mViewport = nullptr;
	mCameraNode = nullptr;
	mSceneMgr = nullptr;
	mRenderWindow = nullptr;
}

void me::OgreCamera::init(Ogre::SceneNode* CameraNode, Ogre::SceneManager* SceneMgr, Ogre::RenderWindow* RenderWindow)
{
	mSceneMgr = SceneMgr;
	mCameraNode= CameraNode;
	mRenderWindow = RenderWindow;
}

void me::OgreCamera::createCamera(const char* name, int nearDist, int farDist, bool autoRadio, int zOrder)
{
	mCamera = mSceneMgr->createCamera(name);
	mCamera->setNearClipDistance(nearDist);
	mCamera->setFarClipDistance(farDist);
	mCamera->setAutoAspectRatio(autoRadio);
	mCameraNode->attachObject(mCamera);
	mViewport = mRenderWindow->addViewport(mCamera,zOrder, 0.5*zOrder,0,0.5,1);
	mViewport->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f));
		
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



