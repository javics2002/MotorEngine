#pragma once

#ifndef __ENTITYCOMPONENT_CAMERA
#define __ENTITYCOMPONENT_CAMERA

#include "Component.h"
#include "Utils/Vector3.h"
#include <string>
#include <list>

namespace me {

	class Transform;

	/**
	The Camera class create camera(Viewer) in scene
	*/
	class __MOTORENGINE_API Camera : public Component
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

		/*
		Default constructor
		*/
		Camera();
		//Destroy om() map saved camera (ogreCamera)
		~Camera();

		/*
		Set the name saved in om() map and used for entity that attached in node
		*/
		inline void setName(std::string name) {
			mName = name;
		}

		inline void setNearDistance(int nearDistance) {
			mNearDistance = nearDistance;
		}

		inline void setFarDistance(int farDistance) {
			mFarDistance = farDistance;
		}

		inline void setAutoRadio(bool autoRadio) {
			mAutoRadio = autoRadio;
		}

		inline void setZOrder(int zOrder) {
			mZOrder = zOrder;
		}

		inline void setLookAt(Vector3 lookAt) {
			mLookAt = lookAt;
		}

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


