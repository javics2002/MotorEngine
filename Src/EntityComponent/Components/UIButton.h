#pragma once

#ifndef __ENTITYCOMPONENT_UIBUTTON
#define __ENTITYCOMPONENT_UIBUTTON

#include "EntityComponent/Components/Component.h"
#include <string>

namespace Ogre {
	class TextAreaOverlayElement;
}

namespace me {
	class UITransform;

	/**
	The UISpriteRenderer class represents a visual object in 2D space as a screen overlay that will be attached to an entity.
	*/
	class __MOTORENGINE_API UIButton : public me::Component
	{
	protected:
		//name for RenderManager map and for entity that attached in node
		std::string mName;
		//name of .png file
		std::string mSpriteName;
		//componenet transform of this.Entity
		me::UITransform* mUITransform;
		//static state of this.Entity 
		bool mStaticObject = false;


		Ogre::TextAreaOverlayElement* mButtonArea;

	public:
		/**
		Construct a new UISpriteRenderer component and save necesary info
		@param name: name saved in RenderManager map and used for entity that attached in node
		@param meshName: name of .png file
		*/
		UIButton();
		//Destroy RenderManager map saved image
		virtual ~UIButton();


		virtual void init(std::string name, std::string materialName, int zOrder);

		/**
		Get info for UITransform, create the Sprite and set the start pos
		*/
		void start() override;

		virtual void execute() {};

		/**
			Set material.
			@param materialName: name of material, as written in MaterialResource.material.
		*/
		void setSpriteMaterial(std::string materialName);

		/**
		Name getter
		*/
		std::string getName();
	};
}
#endif

