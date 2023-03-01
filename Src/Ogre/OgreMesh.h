#pragma once
#ifndef __OGRE_OGREMESH
#define __OGRE_OGREMESH

#include <string>

namespace Ogre {
	class SceneNode;
}

namespace me {
	class OgreMesh
	{

	private:
	protected:
		Ogre::SceneNode* mNode;
		std::string mMeshName;
		


	public:
		OgreMesh(Ogre::SceneNode* mNode,std::string mMeshName);
		~OgreMesh();
		void setTransform(int posX, int posY, int posZ, int scaleX, int scaleY, int scaleZ);
		

	};

}
#endif