#pragma once

#ifndef __ENTITYCOMPONENT_MESHRENDERER
#define __ENTITYCOMPONENT_MESHRENDERER

#include "Component.h"
#include "Utils/Vector3.h"
#include <list>

namespace me {

	class Transform;

	/**
	The MeshRenderer class represents a visual object in 3D space and can be attached to entities.
	*/
	class MeshRenderer : public Component
	{
	private:
	protected:
		//name for om() map and for entity that attached in node
		std::string mName;
		//name of .mesh file
		std::string mMeshName;
		//componenet transform of this.Entity
		Transform* mTransform;
		//static state of this.Entity 
		bool mStaticObject = false;

	public:

		/**
		Construct a new MeshRenderer component and save necesary info
		@param name: name saved in om() map and used for entity that attached in node
		@param meshName: name of .mesh file
		*/
		MeshRenderer(std::string name, std::string meshName);
		//Destroy om() map saved mesh (ogreMesh)
		~MeshRenderer();

		/**
		Get info for mTransform and create ogreMesh and set the start pos
		*/
		void start() override;

		/**
		Update transform info to mesh(ogreMesh)
		*/
		void update() override;

		/**
		 Set material to mesh (ogreMesh).
		 @param materialName: name of material that is written in MaterialResource.material.
		*/
		void setMaterial(std::string materialName);

		/**
		Set it is static entity or not
		*/
		void setStatic(bool stat);

		/**
		Set it is static entity or not
		*/
		std::string getName();
			
	};
}
#endif


