#pragma once
#ifndef __EC_UI_ELEMENT
#define __EC_UI_ELEMENT

#include <EntityComponent/Component.h>
#include "Utils/Vector3.h"
#include "Utils/Vector2.h"

namespace Ogre {
	class Overlay;
	class OverlayContainer;
	class OverlayManager;
}


namespace me {

	/**
	* UIElement represents a graphical user interface (GUI) element that can be displayed on the screen
	* It is a Component that can be attached to an Entity to add user interface functionality to it
	*/

	class UIElement : public me::Component
	{
	public:
		UIElement();
		~UIElement();


		/**
		* Shows the overlay
		*/
		void show(); 

		/**
		* Hides the overlay
		*/
		void hide(); 

		/**
		* Gets the size of the UIElement
		* @return A Vector2<float> representing the width and height of the UIElement
		*/
		Vector2 getSize();

		/**
		* Gets the position of the UIElement
		* @return A Vector2<float> representing the x and y position of the UIElement
		*/
		Vector2 getPos();

		/**
		* Sets the size of the UIElement
		* @param size A Vector2<float> representing the new width and height of the UIElement
		*/
		void setSize(Vector2 size);

		/**
		* Checks if the UIElement is currently visible
		* @return true if the UIElement is visible, false otherwise
		*/
		bool isVisible();

		/**
		* Sets the top position of the UIElement
		* @param top The new top position of the UIElement
		*/
		void setTop(float top);
		/**
		* Sets the left position of the UIElement
		* @param left The new left position of the UIElement
		*/
		void setLeft(float left);

		/**
		* Sets the width of the UIElement
		* @param width The new width of the UIElement
		*/
		void setWidth(float wifth);
		/**
		* Sets the height of the UIElement
		* @param height The new height of the UIElement
		*/
		void setHeight(float height);

		/**
		* Sets whether the UIElement is interactive 
		* @param interactive true if the UIElement is interactive, false otherwise
		*/
		void setInteractive(bool interactive);

		/**
		* Sets whether the UIElement should immediately receive keyboard focus
		* @param focus true if the UIElement should immediately receive keyboard focus, false otherwise
		*/
		void setFocusNow(bool focus);

		/**
		* Gets whether the UIElement is interactive
		* @return true if the UIElement is interactive, false otherwise
		*/
		bool getIsInteractive();
		/**
		* Gets whether the UIElement currently has keyboard focus
		* @return true if the UIElement currently has keyboard focus, false otherwise
		*/
		bool getIsFocusNow();

	protected:

		Ogre::OverlayManager* mOverlayManager;
		Ogre::Overlay* mOverlay;
		Ogre::OverlayContainer* mOverlayContainer;

		bool mInteractive;
		bool mFocus;

		int mElems=0;


	};
}


#endif // !__EC_UI:ELEMENT




