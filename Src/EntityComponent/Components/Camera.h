#pragma once

#ifndef __ENTITYCOMPONENT_CAMERA
#define __ENTITYCOMPONENT_CAMERA

#include "Component.h"
#include "Utils/Vector3.h"
#include "Utils/Vector4.h"
#include <string>
#include <list>

namespace me {

	class Transform;

	/**
	The Camera class create camera(Viewer) in scene
	*/
	class __MOTORENGINE_API Camera : public Component
	{
	protected:
		//Name for RenderManager map and for RenderCamera that attached in node
		std::string mName;
		//Distance from which objects will begin to render
		float mNearDistance;
		//Distance which objects stop rendering
		float mFarDistance;
		//Whether viewport calculates the aspect radio automatically
		bool mAutoRatio;
		//Relative order of viewport
		int mZOrder;
		//Point to look at
		Vector3 mLookAt;
		//Colour of the background
		Vector4 mBackgroundColour;
		//componenet transform of this.Entity
		Transform* mTransform;
		//static state of this.Entity 
		bool mStaticObject = false;

		int x = 0;


	public:
		/*
		Default constructor
		*/
		Camera();
		//Destroy renderManager() map saved camera (RenderCamera)
		~Camera();

		/*
		Set the name saved in renderManager() map and used for entity that attached in node
		*/
		inline void setName(std::string name) {
			mName = name;
		}

		/*
		Set the name saved in renderManager() map and used for entity that attached in node
		*/
		inline std::string getName() {
			return mName;
		}
		/**
		 * Set the distance from which objects will begin to render.
		 * @param nearDistance The distance to set.
		 */
		inline void setNearDistance(float nearDistance) {
			mNearDistance = nearDistance;
		}

		/**
		 * Set the distance at which objects stop rendering.
		 * @param farDistance The distance to set.
		 */
		inline void setFarDistance(float farDistance) {
			mFarDistance = farDistance;
		}
		/**
		 * Set whether the viewport calculates the aspect ratio automatically.
		 * @param autoRatio The value to set.
		 */
		inline void setAutoRadio(bool autoRatio) {
			mAutoRatio = autoRatio;
		}
		/**
		 * Set the relative order of the viewport.
		 * @param zOrder The value to set.
		 */
		inline void setZOrder(int zOrder) {
			mZOrder = zOrder;
		}

		/**
		 * Set the point to look at.
		 * @param lookAt The vector to set.
		 */
		inline void setLookAt(Vector3 lookAt) {
			mLookAt = lookAt;
		}
		/**
		 * Set the color of the background.
		 * @param colour The vector to set.
		 */
		inline void setBackgroundColour(Vector4 colour) {
			mBackgroundColour = colour;
		}

		/**
		Get info for mTransform and create ogreCamera and set the start pos
		*/
		void start() override;

		void init();
		/**
		Update transform info to camera node
		*/
		void update(const double& dt) override;

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

		void setViewportOverlayEnabled(bool enabled);
	};
}
#endif


