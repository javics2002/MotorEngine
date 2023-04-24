#pragma once
#ifndef __RENDER_RENDERCAMERA
#define __RENDER_RENDERCAMERA

#include "MotorEngine/MotorEngineAPI.h"
#include "Utils/Vector3.h"

namespace Ogre {
	class Camera;
	class Viewport;
	class SceneNode;
	class SceneManager;
	class RenderWindow;
	class ColourValue;
}

namespace me {
	/**
	Manages OgreCamera
	*/
	class __MOTORENGINE_API RenderCamera
	{
	protected:
		//Reference to Ogre::Camera
		Ogre::Camera* mCamera ;
		//Reference to Ogre::Viewport of mCamera
		Ogre::Viewport* mViewport ;
		//Reference to Ogre::SceneNode of mCamera
		Ogre::SceneNode* mCameraNode ;
		//Reference to Ogre::SceneManager created by RenderManager
		Ogre::SceneManager* mSceneMgr;
		//Reference to Ogre::RenderWindow created by RenderManager
		Ogre::RenderWindow* mRenderWindow;


	public:
		RenderCamera();
		~RenderCamera();

		//Assign references
		void init(Ogre::SceneNode* CameraNode, Ogre::SceneManager* SceneMgr, Ogre::RenderWindow* RenderWindow );

		/**Create mCamera with this informationand create mViewport for it
		@param name: name of mCamera
		@param nearDist: near clipping plane distancia
		@param farDist: far clipping plane distancia
		@param autoRadio: if viewport calculate aspect radio automatically
		@param zOrder: relative order of mViewport
		*/
		void createCamera(const char* name, float nearDist, float farDist, bool autoRadio, int zOrder, Ogre::ColourValue color);

		//Set position to mCameraNode
		void setPosition(const Vector3& pos);

		void setFixedYAxis(bool bFixed);
		//Set lookAT to mCameraNode
		void lookAt(const Vector3& look);
		/**
		Set dimension to mViewport
		@param left: left point of mViewport in range 0.0 to 1.0
		@param top: top point of mViewport in range 0.0 to 1.0
		@param width: width of mViewport in range 0.0 to 1.0
		@param height: height of mViewport in range 0.0 to 1.0
		*/
		void setViewportDimension(float left, float top, float width, float height);

		
		//void setPosition(Vector3 pos);
		//void lookAt(Vector3 pos);

	};

}
#endif