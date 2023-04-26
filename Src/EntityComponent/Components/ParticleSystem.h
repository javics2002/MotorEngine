#pragma once

#ifndef __ENTITYCOMPONENT_PARTICLESYSTEM
#define __ENTITYCOMPONENT_PARTICLESYSTEM

#include "Component.h"
#include "Utils/Vector3.h"
#include <string>
#include <list>

namespace me {
	class Transform;

	/**
	The ParticleSystem class represents a visual particle system in 3D space and can be attached to entities.
	*/
	class __MOTORENGINE_API ParticleSystem : public Component
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
		Construct a new  particle system component
		*/
		ParticleSystem();
		//Destroy om() map saved particle(ogreParticleSystem)
		~ParticleSystem();

		/**
		Get info for mTransform and create (ogreParticleSystem) and set the start pos
		*/
		void start() override;
		
		/**
		Initialize particle system component in rendermanager
		*/
		void init() ;

		/**
		Update transform info to particle(ogreParticleSystem)
		*/
		void update(const double& dt) override;

		/**
		Set its emitting state
		*/
		void setEmitting(bool emitted);

		/**
		 Set name to mesh (renderMesh in rendermanager array).
		*/
		void setName(std::string name);
		/**
		 Set meshname to mesh (renderMesh in rendermanager array).
		*/
		void setParticleName(std::string particleName);


		/**
		Set its offset position respective to its entity.
		*/
		void setOffsetPos(Vector3 offset);
		/**
		Set its offset scale respective to its entity.
		*/
		void setOffsetScale(Vector3 offset);
			
	};
}
#endif


