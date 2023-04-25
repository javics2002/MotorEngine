#include "RenderMesh.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreQuaternion.h>

me::RenderMesh::RenderMesh(Ogre::SceneNode* node, std::string meshName)
{
	mNode = node;
	mMeshName = meshName;
	Ogre::SceneManager* mSM = mNode->getCreator();

	mEntity = mSM->createEntity(mMeshName);
	mNode->attachObject(mEntity);
	mNode->setVisible(true);
}

me::RenderMesh::~RenderMesh()
{
	Ogre::SceneManager* mSM = mNode->getCreator();
	mNode->detachAllObjects();
	mSM->destroyEntity(mEntity);
	mSM->destroySceneNode(mNode);
}

void me::RenderMesh::setTransform(const Ogre::Vector3f &pos, const Ogre::Vector3f &scale, const Ogre::Quaternion &rot)
{
	mNode->setPosition(pos);
	mNode->setScale(scale);
	mNode->setOrientation(rot);
}

void me::RenderMesh::setPosition(const Ogre::Vector3f &pos)
{
	mNode->setPosition(pos);
}

void me::RenderMesh::setScale(const Ogre::Vector3f &scale)
{
	mNode->setScale(scale);
}

void me::RenderMesh::setRotation(Ogre::Quaternion rot)
{
	mNode->setOrientation(rot);
}

void me::RenderMesh::activeMesh()
{
	mNode->setVisible(true);
}

void me::RenderMesh::desactiveMesh()
{
	mNode->setVisible(false);
}

Ogre::Entity* me::RenderMesh::getOgreEntity()
{
	return mEntity;
}

void me::RenderMesh::setMaterial(std::string materialName)
{
	mMaterialName = materialName;
	mEntity->setMaterialName(materialName);
	
}
