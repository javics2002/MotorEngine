#pragma once
#ifndef __EC_UI_BUTTON
#define __EC_UI_BUTTON

#include "UIElement.h"
#include <functional>
#include <OgreTextAreaOverlayElement.h>

namespace me {

	class UIButton : public me::UIElement
	{
	public:
		UIButton(std::string name,float width,float height, float left, float top);
		~UIButton();

		void update()override;

		/**
		* Method that handles input for the button, called onClick if just clicked
		*/
		void handleInput();


		/**
		* Method that sets the onClick listener for the button, which is a function that
		* will be called when the button is clicked.
		* @param l A std::function<void()> object representing the listener function.
		*/
		void onClick(std::function<void()> l);

	private:
		std::vector<std::function<void()>> mLambda;
		Ogre::TextAreaOverlayElement* mButtonArea;
	};
}


#endif // !__EC_UI_BUTTON


