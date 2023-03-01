#pragma once
#ifndef __OGRE_OGREMESH
#define __OGRE_OGREMESH

#include <string>

namespace Ogre {
	class SceneNode;
}

namespace me {

	//Class to create renderizable object with mesh
	class OgreMesh
	{

	private:
	protected:
		//Reference to Ogre::SceneNode for renderize
		Ogre::SceneNode* mNode;
		//Name of mesh that used
		std::string mMeshName;
		


	public:
		/**
		Assign information and create Ogre::Entity with the given mesh and attach to mNode
		@param node: mNode for attach Ogre::Entity created
		@param meshName: name of resource (type mesh) that we used for create Ogre::Entity. 
		Must be writted in resource.cfg (.mesh inside Zip or FileSystem)
		*/
		OgreMesh(Ogre::SceneNode* node,std::string meshName);
		~OgreMesh();
		//Set position and scale of mNode
		void setTransform(int posX, int posY, int posZ, int scaleX, int scaleY, int scaleZ);
		

	};

}
#endif