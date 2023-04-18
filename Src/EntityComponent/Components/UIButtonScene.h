#pragma once

#ifndef __ENTITYCOMPONENT_UISBUTTONSCENE
#define __ENTITYCOMPONENT_UISBUTTONSCENE

#include "Component.h"
#include <string>
#include "UIElement.h"

namespace Ogre {
	class TextAreaOverlayElement;
}

namespace me {
	class UITransform;

	/**
	The UISpriteRenderer class represents a visual object in 2D space as a screen overlay that will be attached to an entity.
	*/
	class __MOTORENGINE_API UIButtonScene : public UIElement
	{
	private:
	protected:
		//name for RenderManager map and for entity that attached in node
		std::string mName;
		//name of .png file
		std::string mSpriteName;
		//componenet transform of this.Entity
		UITransform* mUITransform;
		//static state of this.Entity 
		bool mStaticObject = false;

		std::string mNewScene;

		Ogre::TextAreaOverlayElement* mButtonArea;

		int x = 0;

	public:

		/**
		Construct a new UISpriteRenderer component and save necesary info
		@param name: name saved in RenderManager map and used for entity that attached in node
		@param meshName: name of .png file
		*/
		UIButtonScene();
		//Destroy RenderManager map saved image
		~UIButtonScene();

		void init(std::string name, std::string materialName, float width, float height, float left, float top);

		/**
		Get info for UITransform, create the Sprite and set the start pos
		*/
		void start() override;

		void setNewScene(std::string newScene);


		/**
		Update UITransform info to image
		*/
		void update() override;

		void execute();

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

