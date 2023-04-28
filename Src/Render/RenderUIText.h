#pragma once
#ifndef __RENDER_RENDERUITEXT
#define __RENDER_RENDERUITEXT

#include "MotorEngine/MotorEngineAPI.h"
#include "Utils/Vector2.h"
#include <string>

namespace Ogre {
	class Overlay;
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

		//Reference to Ogre::OverlayElement (Panel) for renderization
		Ogre::TextAreaOverlayElement* mPanel;

	public:
		/**
		Assign information and create Ogre::OverlayElement with the given sprite	(and attach to mNode???)
		@param panel: OverlayElement from which position, dimensions, etc. will be manipulated.
		@param spriteName: name of the source .png file.
		Must be included in resource.cfg (.png inside Zip or FileSystem)
		*/
		RenderUIText(Ogre::Overlay* overlay, Ogre::TextAreaOverlayElement* panel, std::string spriteName, int zOrder);

		~RenderUIText();

		//Set position, rotation and scale of panel in Overlay
		void setTransform(Vector2 pos, Vector2 scale, float rot);

		void setPosition(Vector2 pos);

		void setScale(Vector2 scale);

		void setRotation(float rot);

		void setText(std::string text);

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