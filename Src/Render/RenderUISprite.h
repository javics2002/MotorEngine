#pragma once
#ifndef __RENDER_RENDERUISPRITE
#define __RENDER_RENDERUISPRITE

#include "MotorEngine/MotorEngineAPI.h"
#include "Utils/Vector2.h"
#include <string>

namespace Ogre {
	class Overlay;
	class OverlayElement;
}

namespace me {

	//Class to create renderizable object with Sprite
	class __MOTORENGINE_API RenderUISprite
	{

	private:
	protected:
		//Reference to Ogre::Overlay (Panel) for transformation
		Ogre::Overlay* mOverlay;

		//Reference to Ogre::OverlayElement (Panel) for renderization
		Ogre::OverlayElement* mPanel;

		//Name of sprite used
		std::string mSpriteName;

		//Name of Material used
		std::string mMaterialName;

	public:
		/**
		Assign information and create Ogre::OverlayElement with the given sprite	(and attach to mNode???)
		@param panel: OverlayElement from which position, dimensions, etc. will be manipulated.
		@param spriteName: name of the source .png file.
		Must be included in resource.cfg (.png inside Zip or FileSystem)
		*/
		RenderUISprite(Ogre::Overlay* overlay, Ogre::OverlayElement* panel, std::string spriteName,int zOrder);

		~RenderUISprite();

		//Set position, rotation and scale of panel in Overlay
		void setTransform(Vector2 pos, Vector2 scale, float rot);

		void setPosition(Vector2 pos);

		void setScale(Vector2 scale);

		void setRotation(float rot);

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