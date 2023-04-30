#pragma once
#ifndef __RENDER_RENDERUITEXT
#define __RENDER_RENDERUITEXT

#include "MotorEngine/MotorEngineAPI.h"
#include "Utils/Vector2.h"
#include "Utils/Vector3.h"
#include <string>

namespace Ogre {
	class Overlay;
	class OverlayContainer;
	class OverlayElement;
	class TextAreaOverlayElement;
}

namespace me {

	//Class to create renderizable object with Sprite
	class __MOTORENGINE_API RenderUIText
	{

	private:
	protected:
		//Reference to Ogre::Overlay (Panel) for transformation
		Ogre::Overlay* mOverlay;

		Ogre::OverlayContainer* mCont;

		//Reference to Ogre::OverlayElement (Panel) for renderization
		Ogre::TextAreaOverlayElement* mTextArea;

	public:
		/**
		Assign information and create Ogre::OverlayElement with the given sprite	(and attach to mNode???)
		@param panel: OverlayElement from which position, dimensions, etc. will be manipulated.
		@param text: name of the text to render
		Must be included in resource.cfg (.png inside Zip or FileSystem)
		*/
		RenderUIText(std::string name, std::string text, int zOrder,
			float positionX,float positionY,float dimensionX, float dimensionY, std::string fontName , float charHeight, Vector3 color);

		~RenderUIText();

		//Set position, rotation and scale of panel in Overlay
		void setTransform(Vector2 pos, Vector2 scale, float rot);


		/**
		* Set the font used by the UIText instance
		* @param fontName The name of the font to use
		*/
		void setPosition(Vector2 pos);


		/**
		* Set the font used by the UIText instance
		* @param fontName The name of the font to use
		*/
		void setDimensions(Vector2 scale);


		/**
		* Set the font used by the UIText instance
		* @param fontName The name of the font to use
		*/
		void setRotation(float rot);
		
		/**
		* Set the font used by the UIText instance
		* @param fontName The name of the font to use
		*/
		void setText(std::string text);

		/**
		* Set the font used by the UIText instance
		* @param fontName The name of the font to use
		*/
		void setFont(std::string fontName);

		/**
		* Set the font used by the UIText instance
		* @param fontName The name of the font to use
		*/
		void setCharHeight(float charHeight);	
		
		
		/**
		* Set the font used by the UIText instance
		* @param fontName The name of the font to use
		*/
		void setColour(Vector3 colour);

		/*
		* Set whether the UIText instance is active or not
		* @param active True if the UIText should be active, false otherwise
		*/
		void setActive(bool active);

		/**
		Return the Ogre::OverlayElement asociated
		*/
		Ogre::OverlayElement* getOgreOverlayElement();

		/**
		Return the Ogre::Overlay that contains the OverlayElement
		*/
		Ogre::Overlay* getOgreOverlay();

		/**
		Assign a material to the panel (and thus, a sprite) by name
		@param materialName: Name of the target Material
		Must be included in MaterialResource.material
		*/
		void setMaterial(std::string materialName);
	};

}
#endif