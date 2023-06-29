#include "RenderParticleSystem.h"
#include <OgreSceneManager.h>
#include <OgreParticleSystemManager.h>
#include "MotorEngine/MotorEngineError.h"
#include <OgreParticleSystem.h>
#include <OgreSceneNode.h>
#include <OgreQuaternion.h>
#include "MotorEngine/SceneManager.h"
#include <iostream>

me::RenderParticleSystem::RenderParticleSystem(std::string name,Ogre::SceneNode* node, std::string particleName, bool &success)
{
	mNode = node;
	mParticleName = particleName;
	mName = name;
	Ogre::SceneManager* mSM = mNode->getCreator();

	if (Ogre::ParticleSystemManager::getSingleton().getTemplate(mParticleName) == 0) {
		errorManager().throwMotorEngineError(mParticleName + " was not registered in the .particle file", " Can´t create particle system.");
		success = false;
		sceneManager().quit();
		return;
	}
	mParticleSystem = mSM->createParticleSystem(mName, mParticleName);
	mParticleSystem->setEmitting(false);
	mParticleSystem->setKeepParticlesInLocalSpace(true);
	mNode->attachObject(mParticleSystem);
	success = true;
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


