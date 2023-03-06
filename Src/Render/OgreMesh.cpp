#include "OgreMesh.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreQuaternion.h>

me::OgreMesh::OgreMesh(Ogre::SceneNode* node, std::string meshName)
{
	mNode = node;
	mMeshName = meshName;
	Ogre::SceneManager* mSM = mNode->getCreator();

	mEntity = mSM->createEntity(mMeshName);
	mNode->attachObject(mEntity);
	mNode->setVisible(true);
}

me::OgreMesh::~OgreMesh()
{
}

void me::OgreMesh::setTransform(const Ogre::Vector3f &pos, const Ogre::Vector3f &scale, const Ogre::Quaternion &rot)
{
	mNode->setPosition(pos);
	mNode->setScale(scale);
	mNode->setOrientation(rot);
}

void me::OgreMesh::setPosition(const Ogre::Vector3f &pos)
{
	mNode->setPosition(pos);
}

void me::OgreMesh::setScale(const Ogre::Vector3f &scale)
{
	mNode->setScale(scale);
}

void me::OgreMesh::setRotation(Ogre::Quaternion rot)
{
	mNode->setOrientation(rot);
}

void me::OgreMesh::setMaterial(std::string materialName)
{
	mMaterialName = materialName;
	mEntity->setMaterialName(materialName);
	
}
