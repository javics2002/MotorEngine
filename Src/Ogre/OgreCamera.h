#pragma once
namespace Ogre {
	class Camera;
	class Viewport;
	class SceneNode;
	class SceneManager;
	class RenderWindow;
}

namespace me {
	class OgreCamera
	{

	private:
	protected:

		Ogre::Camera* mCamera ;
		Ogre::Viewport* mViewport ;
		Ogre::SceneNode* mCameraNode ;
		Ogre::SceneManager* mSceneMgr;
		Ogre::RenderWindow* mRenderWindow;


	public:
		OgreCamera();
		~OgreCamera();
		void init(Ogre::SceneNode* CameraNode, Ogre::SceneManager* SceneMgr, Ogre::RenderWindow* RenderWindow );
		void createCamera(const char* name, int nearDist, int farDist, bool autoRadio);
		void renderCamera();


		void setPosition(int x, int y, int z);
		void lookAt(int x, int y, int z);
		void setViewportDimension(float left, float top, float width, float height);

		//void setPosition(Vector3 pos);
		//void lookAt(Vector3 pos);

	};

}