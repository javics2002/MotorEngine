#pragma once

#ifndef __ENTITYCOMPONENT_PARTICLESYSTEM
#define __ENTITYCOMPONENT_PARTICLESYSTEM

#include "Component.h"
#include "Utils/Vector3.h"
#include <list>

namespace me {

	class Transform;

	/**
	The ParticleSystem class represents a visual particle system in 3D space and can be attached to entities.
	*/
	class ParticleSystem : public Component
	{
	private:
	protected:
		//name for om() map and for particle system that attached in node
		std::string mName;
		//name of particle that is written int ParticleResource.particle
		std::string mParticleName;
		//componenet transform of this.Entity
		Transform* mTransform;

		Vector3 mOffsetPos;
		Vector3 mOffsetScale;
		

	public:

		/**
		Construct a new  particle system component and save necesary info
		@param name: name saved in om() map and used for particle that attached in node
		@param particleName: name of particle that is written int ParticleResource.particle
		*/
		ParticleSystem(std::string name, std::string particleName);
		//Destroy om() map saved particle(ogreParticleSystem)
		~ParticleSystem();

		/**
		Get info for mTransform and create (ogreParticleSystem) and set the start pos
		*/
		void start() override;

		/**
		Update transform info to particle(ogreParticleSystem)
		*/
		void update() override;

		/**
		Set it emitting state
		*/
		void setEmitting(bool emitted);

		void setOffsetPos(Vector3 offset);
		void setOffsetScale(Vector3 offset);
			
	};
}
#endif


