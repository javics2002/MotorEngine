#pragma once

namespace Ogre {
	class Camera;
	class SceneNode;
	class SceneManager;
}

namespace me {
	class OgreCamera
	{

	private:
	protected:

		Ogre::Camera* mCamera = nullptr;
		Ogre::SceneNode* mCameraNode = nullptr;


	public:
		OgreCamera();
		~OgreCamera();

	};

}