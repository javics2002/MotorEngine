#pragma once

#ifndef __ENTITYCOMPONENT_CAMERA
#define __ENTITYCOMPONENT_CAMERA

#include "Component.h"
#include "Utils/Vector3.h"
#include <list>

namespace me {

	class Transform;

	/**
	The Camera class create camera(Viewer) in scene
	*/
	class Camera : public Component
	{
	private:
	protected:
		//name for om() map and for ogreCamera that attached in node
		std::string mName;
		int mNearDistance;
		int mFarDistance;
		bool mAutoRadio;
		int mZOrder;
		Vector3 mLookAt;
		//componenet transform of this.Entity
		Transform* mTransform;
		//static state of this.Entity 
		bool mStaticObject = true;

	public:

		/**
		Construct a new Camera component and save necesary info
		@param name: name saved in om() map and used for entity that attached in node
		*/
		Camera(std::string name, int nearDist, int farDist, bool autoRadio, int zOrder,Vector3 lookAt);
		//Destroy om() map saved camera (ogreCamera)
		~Camera();

		/**
		Get info for mTransform and create ogreCamera and set the start pos
		*/
		void start() override;

		/**
		Update transform info to camera node
		*/
		void update() override;

		/**
		Set it is static entity or not
		*/
		void setStatic(bool stat);

		/**
		Set dimension to the viewport of the camera with this name
		@param name: name of camera
		@param left: left point of viewport in range 0.0 to 1.0
		@param top: top point of viewport in range 0.0 to 1.0
		@param width: width of viewport in range 0.0 to 1.0
		@param height: height of viewport in range 0.0 to 1.0
		@return false: if it doesn't exist
		@return true: if succeed
		*/
		void setViewportDimension(float left, float top, float width, float height);

				
	};
}
#endif


