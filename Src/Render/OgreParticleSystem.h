#pragma once
#ifndef __OGRE_OGRE_PARTICLESYSTEM
#define __OGRE_OGRE_PARTICLESYSTEM

#include <string>
#include <OgreVector3.h>

namespace Ogre {
	class SceneNode;
	class Quaternion;
	class ParticleSystem;
}

namespace me {

	//Class to create renderizable particle system 
	class OgreParticleSystem
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
		OgreParticleSystem(std::string name,Ogre::SceneNode* node,std::string particleName);
		~OgreParticleSystem();
		//Set position, rotation and scale of mNode
		void setTransform(const Ogre::Vector3f &pos, const Ogre::Vector3f &scale, const Ogre::Quaternion &rot);
		void setPosition(const Ogre::Vector3f &pos);
		void setScale(const Ogre::Vector3f &scale);
		void setRotation(Ogre::Quaternion rot);

		//set particle system emitting state
		void setEmitting(bool emitted);
		

	};

}

#endif