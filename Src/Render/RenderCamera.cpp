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

void me::RenderCamera::createCamera(const char* name, float nearDist, float farDist, bool autoRadio, int zOrder, Ogre::ColourValue color)
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
	mViewport->setOverlaysEnabled(true);
}


me::RenderCamera::~RenderCamera()
{
	mCameraNode->detachAllObjects();
	mSceneMgr->destroyCamera(mCamera);
	mSceneMgr->destroySceneNode(mCameraNode);
}


void me::RenderCamera::setPosition(const Vector3& pos)
{
	mCameraNode->setPosition(pos.v3ToOgreV3());
}

void me::RenderCamera::lookAt(const Vector3& look)
{
	mCameraNode->lookAt(look.v3ToOgreV3(), Ogre::Node::TS_WORLD);
}

void me::RenderCamera::setViewportDimension(float left, float top, float width, float height)
{
	mViewport->setDimensions(left, top, width, height);
	
}





