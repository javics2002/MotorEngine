#include "RenderParticleSystem.h"
#include <OgreSceneManager.h>
#include <OgreParticleSystem.h>
#include <OgreSceneNode.h>
#include <OgreQuaternion.h>

me::RenderParticleSystem::RenderParticleSystem(std::string name,Ogre::SceneNode* node, std::string particleName)
{
	mNode = node;
	mParticleName = particleName;
	mName = name;
	Ogre::SceneManager* mSM = mNode->getCreator();

	mParticleSystem = mSM->createParticleSystem(mName, mParticleName);
	mParticleSystem->setEmitting(false);
	mParticleSystem->setKeepParticlesInLocalSpace(true);
	mNode->attachObject(mParticleSystem);
}

me::RenderParticleSystem::~RenderParticleSystem()
{
	Ogre::SceneManager* mSM = mNode->getCreator();
	mNode->detachAllObjects();
	mSM->destroyParticleSystem(mParticleSystem);
	mSM->destroySceneNode(mNode);
}

void me::RenderParticleSystem::setTransform(const Ogre::Vector3f &pos, const Ogre::Vector3f &scale, const Ogre::Quaternion &rot)
{
	mNode->setPosition(pos);
	mNode->setScale(scale);
	mNode->setOrientation(rot);
}

void me::RenderParticleSystem::setPosition(const Ogre::Vector3f &pos)
{
	mNode->setPosition(pos);
}

void me::RenderParticleSystem::setScale(const Ogre::Vector3f &scale)
{
	mNode->setScale(scale);
}

void me::RenderParticleSystem::setRotation(Ogre::Quaternion rot)
{
	mNode->setOrientation(rot);
}

void me::RenderParticleSystem::setEmitting(bool emitted)
{
	mParticleSystem->setEmitting(emitted);
}


