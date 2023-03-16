#pragma once
#ifndef __EC_UI_TEXT
#define __EC_UI_TEXT

#include "Component.h"
#include <string>
#include "Utils/Vector3.h"
#include "Utils/Vector4.h"
#include "UIElement.h"

#include <OgreTextAreaOverlayElement.h>

namespace me {
	class UIText : public me::UIElement
	{
		UIText(std::string name, std::string fontName, float posX, float poxY, float width, float height, std::string text, Vector4 textColor);
		~UIText();


		/**
		* Set the position of the UIText instance
		* @param x The x coordinate of the position
		* @param y The y coordinate of the position
		*/
		void setPosition(float x, float y);


		/**
		* Set the size of the UIText instance
		* @param w The width of the UIText
		* @param h The height of the UIText
		*/
		void setSize(float w, float h);



		/**
		* Set the font used by the UIText instance
		* @param fontName The name of the font to use
		*/
		void setFont(std::string fontName);


		/**
		* Set the text displayed by the UIText instance
		* @param newText The new text to display
		*/
		void setText(std::string newText);


		/**
		* Set the color of the text displayed by the UIText instance
		* @param newColor The new color of the text
		*/
		void setTextColor(Vector4 newColor);


		/**
		* Set the width of the UIText instance
		* @param widthValue The new width of the UIText
		*/
		void setWidth(double widthValue);


		/**
		* Set the height of the UIText instance
		* @param heightValue The new height of the UIText
		*/
		void setHeight(double heightValue);


		/*
		* Set whether the UIText instance is active or not
		* @param active True if the UIText should be active, false otherwise
		*/
		void setActive(bool active);


		/**
		* Set the alignment of the text displayed by the UIText instance
		* @param a The new alignment of the text
		*/
		void setTextAligment(Ogre::TextAreaOverlayElement::Alignment a);

	private:

		// Pointer to the text area overlay element
		Ogre::TextAreaOverlayElement* mTextArea;
		// The alignment of the text displayed 
		Ogre::TextAreaOverlayElement::Alignment mAlignment;
	};
}


#endif // !__EC_UI_TEXT



