#include "OgreMesh.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

me::OgreMesh::OgreMesh(Ogre::SceneNode* node, std::string meshName)
{
	mNode = node;
	mMeshName = meshName;
	Ogre::SceneManager* mSM = mNode->getCreator();

	Ogre::Entity* ent = mSM->createEntity(mMeshName);
	mNode->attachObject(ent);
	mNode->setVisible(true);
}

me::OgreMesh::~OgreMesh()
{
}

void me::OgreMesh::setTransform(int posX, int posY, int posZ, int scaleX, int scaleY, int scaleZ)
{
	mNode->setPosition(posX, posY, posZ);
	mNode->setScale(scaleX, scaleY, scaleZ);
}
