#include "OgreParticleSystem.h"
#include <OgreSceneManager.h>
#include <OgreParticleSystem.h>
#include <OgreSceneNode.h>
#include <OgreQuaternion.h>

me::OgreParticleSystem::OgreParticleSystem(std::string name,Ogre::SceneNode* node, std::string particleName)
{
	mNode = node;
	mParticleName = particleName;
	mName = name;
	Ogre::SceneManager* mSM = mNode->getCreator();

	mParticleSystem = mSM->createParticleSystem(mName, mParticleName);
	mParticleSystem->setEmitting(false);
	mNode->attachObject(mParticleSystem);
}

me::OgreParticleSystem::~OgreParticleSystem()
{
	
	Ogre::SceneManager* mSM = mNode->getCreator();
	mNode->detachAllObjects();
	mSM->destroyParticleSystem(mParticleSystem);
	mSM->destroySceneNode(mNode);

}

void me::OgreParticleSystem::setTransform(const Ogre::Vector3f &pos, const Ogre::Vector3f &scale, const Ogre::Quaternion &rot)
{
	mNode->setPosition(pos);
	mNode->setScale(scale);
	mNode->setOrientation(rot);
}

void me::OgreParticleSystem::setPosition(const Ogre::Vector3f &pos)
{
	mNode->setPosition(pos);
}

void me::OgreParticleSystem::setScale(const Ogre::Vector3f &scale)
{
	mNode->setScale(scale);
}

void me::OgreParticleSystem::setRotation(Ogre::Quaternion rot)
{
	mNode->setOrientation(rot);
}

void me::OgreParticleSystem::setEmitting(bool emitted)
{
	mParticleSystem->setEmitting(emitted);
}


