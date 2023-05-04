#pragma once
#ifndef __RENDER_RENDERPARTICLESYSTEM
#define __RENDER_RENDERPARTICLESYSTEM

#include "MotorEngine/MotorEngineAPI.h"
#include <string>
#include <OgreVector3.h>

namespace Ogre {
	class SceneNode;
	class Quaternion;
	class ParticleSystem;
}

namespace me {

	//Class to create renderizable particle system 
	class __MOTORENGINE_API RenderParticleSystem
	{

	private:
	protected:
		//Reference to Ogre::SceneNode for renderize
		Ogre::SceneNode* mNode;
		//Reference to Ogre::ParticleSystem for renderize
		Ogre:: ParticleSystem* mParticleSystem;
		//Name of particle that used
		std::string mParticleName;
		//Name of particle system
		std::string mName;
		


	public:
		/**
		Assign information and create Ogre::ParticleSystem with the given mesh and attach to mNode
		@param name: name for particle system
		@param node: mNode for attach Ogre::ParticleSystem created
		@param meshName: name of resource (type mesh) that we used for create Ogre::Entity. 
		Must be writted in resource.cfg (.mesh inside Zip or FileSystem)
		*/
		RenderParticleSystem(std::string name, Ogre::SceneNode* node, std::string particleName);
		~RenderParticleSystem();

		/**
		* Set position, scale and rotation to the ParticleNode
		* @param pos : position of particleNode
		* @param scale : scale of particleNode
		* @param rot : rotation of particleNode
		*/
		void setTransform(const Ogre::Vector3f &pos, const Ogre::Vector3f &scale, const Ogre::Quaternion &rot);

		/**
		* Set position
		* @param pos : position of particleNode
		*/
		void setPosition(const Ogre::Vector3f &pos);

		/**
		* Set scale to the ParticleNode
		* @param scale : scale of particleNode
		*/
		void setScale(const Ogre::Vector3f &scale);

		/**
		* Set rotation to the ParticleNode
		* @param rot : rotation of particleNode
		*/
		void setRotation(Ogre::Quaternion rot);


		/*
		* Set whether the ParticleSystem instance is active or not
		* @param emitted True if the ParticleSystem should be active, false otherwise
		*/
		void setEmitting(bool emitted);
		

	};

}

#endif