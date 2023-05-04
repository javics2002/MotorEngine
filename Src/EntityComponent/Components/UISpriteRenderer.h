#pragma once

#ifndef __ENTITYCOMPONENT_UISPRITERENDERER
#define __ENTITYCOMPONENT_UISPRITERENDERER

#include "Component.h"
#include <string>

namespace me {
	class UITransform;

	/**
	The UISpriteRenderer class represents a visual object in 2D space as a screen overlay that will be attached to an entity.
	*/
	class __MOTORENGINE_API UISpriteRenderer : public Component
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

		int mZOrder;

	public:

		/**
		Construct a new UISpriteRenderer component and save necesary info
		@param name: name saved in RenderManager map and used for entity that attached in node
		@param meshName: name of .png file
		*/
		UISpriteRenderer();
		//Destroy RenderManager map saved image
		~UISpriteRenderer();

		void init(std::string name, std::string spriteName, int zOrder);

		/**
		Get info for UITransform, create the Sprite and set the start pos
		*/
		void start() override;

		/**
		Update UITransform info to image
		*/
		void update(const double& dt) override;

		/**
		Set it is static entity or not
		@param stat : true if static, false if not
		*/
		void setStatic(bool stat);

		/**
		Set the zOrder
		@param zOrder : Determines the depth of the overlay
		*/
		void setZOrder(int zOrder);

		/*
		resets the sprite material
		*/
		void resetSpriteMaterial();

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

