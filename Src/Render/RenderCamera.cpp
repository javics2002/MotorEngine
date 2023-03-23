#include "RenderCamera.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"
#include "OgreViewport.h"
#include <string>


me::RenderCamera::RenderCamera()
{
	mCamera = nullptr;
	mViewport = nullptr;
	mCameraNode = nullptr;
	mSceneMgr = nullptr;
	mRenderWindow = nullptr;
}

void me::RenderCamera::init(Ogre::SceneNode* CameraNode, Ogre::SceneManager* SceneMgr, Ogre::RenderWindow* RenderWindow)
{
	mSceneMgr = SceneMgr;
	mCameraNode= CameraNode;
	mRenderWindow = RenderWindow;
}

void me::RenderCamera::createCamera(const char* name, int nearDist, int farDist, bool autoRadio, int zOrder, Ogre::ColourValue color)
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


me::RenderCamera::~RenderCamera()
{
	mCameraNode->detachAllObjects();
	mSceneMgr->destroyCamera(mCamera);
	mSceneMgr->destroySceneNode(mCameraNode);
}


void me::RenderCamera::setPosition(const Ogre::Vector3f &pos)
{
	mCameraNode->setPosition(pos);
}

void me::RenderCamera::lookAt(const Ogre::Vector3f &look)
{
	mCameraNode->lookAt(look, Ogre::Node::TS_WORLD);
}

void me::RenderCamera::setViewportDimension(float left, float top, float width, float height)
{
	mViewport->setDimensions(left, top, width, height);
	
}





