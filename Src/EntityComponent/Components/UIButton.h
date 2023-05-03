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
		//name for entity that attached in node
		std::string mName;
		//name of .png file
		std::string mSpriteName;
		//componenet transform of this.Entity
		me::UITransform* mUITransform;
		//static state of this.Entity 
		bool mStaticObject = false;

		Ogre::TextAreaOverlayElement* mButtonArea;
	public:
		UIButton();
		~UIButton();

		virtual void init(std::string name, std::string materialName, int zOrder);

		/**
		Get info for UITransform, create the Sprite and set the start pos
		*/
		virtual void start() override;

		/**
		"Inherited method that will contain the corresponding action for each button.
		*/
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

