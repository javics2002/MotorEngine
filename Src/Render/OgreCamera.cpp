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

void me::OgreCamera::createCamera(const char* name, int nearDist, int farDist, bool autoRadio, int zOrder, Ogre::ColourValue color)
{
	mCamera = mSceneMgr->createCamera(name);
	mCamera->setNearClipDistance(nearDist);
	mCamera->setFarClipDistance(farDist);
	mCamera->setAutoAspectRatio(autoRadio);
	mCameraNode->attachObject(mCamera);
	mViewport = mRenderWindow->addViewport(mCamera,zOrder);
	if (zOrder > 0)
	{
		mViewport->setClearEveryFrame(false);
	}
	mViewport->setBackgroundColour(color);
	mViewport->setOverlaysEnabled(false);



		
}


me::OgreCamera::~OgreCamera()
{
	mCameraNode->detachAllObjects();
	mSceneMgr->destroyCamera(mCamera);
	mSceneMgr->destroySceneNode(mCameraNode);
}


void me::OgreCamera::setPosition(const Ogre::Vector3f &pos)
{
	mCameraNode->setPosition(pos);
}

void me::OgreCamera::lookAt(const Ogre::Vector3f &look)
{
	mCameraNode->lookAt(look, Ogre::Node::TS_WORLD);
}

void me::OgreCamera::setViewportDimension(float left, float top, float width, float height)
{
	mViewport->setDimensions(left, top, width, height);
	
}





