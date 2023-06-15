#pragma once

#ifndef __ENTITYCOMPONENT_UIBUTTON
#define __ENTITYCOMPONENT_UIBUTTON

#include "EntityComponent/Component.h"
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

		/**
		Calls RenderManager to create a 2D sprite in the overlay.
		@param name: Name of Ogre::OverlayElement &&unordered_map
		@param nameMesh: Name of file (xxx.png)
		@param zOrder: a value that stablishes if a button is in front or behind something.
		@return false: if renamed
		@return true: if succeed
		*/
		bool createSprite(std::string name, std::string materialName, int zOrder);

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

