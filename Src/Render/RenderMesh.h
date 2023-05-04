#pragma once
#ifndef __RENDER_RENDERMESH
#define __RENDER_RENDERMESH

#include "MotorEngine/MotorEngineAPI.h"
#include "Utils/Vector4.h"
#include <string>

namespace Ogre {
	class SceneNode;
	class Entity;
}

namespace me {
	class Vector3;

	//Class to create renderizable object with mesh
	class __MOTORENGINE_API RenderMesh
	{

	private:
	protected:
		//Reference to Ogre::SceneNode for renderize
		Ogre::SceneNode* mNode;
		//Reference to Ogre::Entity for renderize
		Ogre::Entity* mEntity;
		//Name of mesh that used
		std::string mMeshName;
		std::string mMaterialName;

	public:

		/**
		Assign information and create Ogre::Entity with the given mesh and attach to mNode
		@param node: mNode for attach Ogre::Entity created
		@param meshName: name of resource (type mesh) that we used for create Ogre::Entity. 
		Must be writted in resource.cfg (.mesh inside Zip or FileSystem)
		*/
		RenderMesh(Ogre::SceneNode* node,std::string meshName);
		~RenderMesh();

		/**
		Set Transform info to the mesh 
		@param pos: position of ogreMesh
		@param scale: scale of ogreMesh
		@param rot: rotation of ogreMesh
		*/
		void setTransform(const me::Vector3 &pos, const me::Vector3 &scale, const me::Vector4 &rot);

		/**
		Set position info to the mesh
		@param pos: position of ogreMesh
		*/
		void setPosition(const me::Vector3 &pos);

		/**
		Set scale info to the mesh
		@param scale: scale of ogreMesh
		*/
		void setScale(const me::Vector3 &scale);

		/**
		Set rotation info to the mesh
		@param rot: rotation of ogreMesh
		*/
		void setRotation(me::Vector4 rot);


		/**
		Active mesh
		*/
		void activeMesh();

		/**
		Desactive mesh
		*/
		void desactiveMesh();

		/**
		Return the Ogre::Entity asociated
		*/
		Ogre::Entity* getOgreEntity();

		/**
		Assign material name to entity
		@param materialName: name of material that we used 
		Must be writted in MaterialResource.material
		*/
		void setMaterial(std::string materialName);
		
	};

}
#endif