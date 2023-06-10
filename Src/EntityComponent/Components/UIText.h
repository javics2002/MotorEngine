#pragma once
#ifndef __ENTITYCOMPONETN_UITEXT
#define __ENTITYCOMPONETN_UITEXT

#include "Component.h"
#include <string>

namespace Ogre {
	class TextAreaOverlayElement;
	class ColourValue;
}

namespace me {
	class UITransform;
	class Vector2;
	class Vector3;
	class RenderUIText;

	class __MOTORENGINE_API UIText : public me::Component
	{
	public:
		UIText();
		~UIText();

		void start() override;

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
		Sets name and zOrder and creates a render overlay with custom text and font.
		@param name
		@param text
		@param zOrder
		@param fontName
		*/
		bool setTextInfo(std::string name, std::string text, int zOrder, std::string fontName);

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
		void setColour(Vector3 newColor);


		/**
		* Set the colorBottom of the text displayed by the UIText instance
		* @param newColor The new color of the text
		*/
		void setColourBottom(Vector3 newColor);


		/**
		* Set the colorTop of the text displayed by the UIText instance
		* @param newColor The new color of the text
		*/
		void setColourTop(Vector3 newColor);

		/**
		* Set the height of the UIText instance
		* @param heightValue The new height of the UIText
		*/
		void setCharHeight(double heightValue);


		/*
		* Set whether the UIText instance is active or not
		* @param active True if the UIText should be active, false otherwise
		*/
		void setActive(bool active);



	private:

		//name for RenderManager map and for entity that attached in node
		std::string mName;
		//name of .png file
		std::string mSpriteName;
		//componenet transform of this.Entity
		UITransform* mUITransform;
		//static state of this.Entity 
		bool mStaticObject = false;

		RenderUIText* mRenderUIText;

		int mZOrder;
	};
}


#endif // !__EC_UI_TEXT



