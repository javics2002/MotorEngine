#include "RenderMesh.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>
#include "Utils/Vector3.h"

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

void me::RenderMesh::setTransform(const me::Vector3& pos, const me::Vector3& scale, const me::Vector4& rot)
{
	mNode->setPosition(pos.v3ToOgreV3());
	mNode->setScale(scale.v3ToOgreV3());
	mNode->setOrientation(rot.v4ToOgreQuaternion());
}

void me::RenderMesh::setPosition(const me::Vector3& pos)
{
	mNode->setPosition(pos.v3ToOgreV3());
}

void me::RenderMesh::setScale(const me::Vector3& scale)
{
	mNode->setScale(scale.v3ToOgreV3());
}

void me::RenderMesh::setRotation(me::Vector4 rot)
{
	mNode->setOrientation(rot.v4ToOgreQuaternion());
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
