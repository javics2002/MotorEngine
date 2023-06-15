#include "ParticleSystem.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Transform.h"
#include "Utils/Vector3.h"
#include <OgreQuaternion.h>
#include <OgreVector3.h>

using namespace me;

ParticleSystem::ParticleSystem()
{

	
}

ParticleSystem::~ParticleSystem()
{
	renderManager().destroyMesh(mName);
	renderManager().destroyParticle(mParticleName);
}

void ParticleSystem::start()
{
	mTransform = getEntity()->getComponent<Transform>("transform");
	renderManager().setParticleTransform(mName, mTransform->getPosition(), mTransform->getScale(), mTransform->getRotation());
}

void me::ParticleSystem::init()
{
	if (mName.size() > 0)
	renderManager().createParticle(mName, mParticleName);
}

void ParticleSystem::update(const double& dt)
{
	Vector3 pos = mTransform->getPosition() + mOffsetPos;
	Vector3 scale = mTransform->getScale() + mOffsetScale;
	renderManager().setParticleTransform(mName, pos, scale, mTransform->getRotation());
	//{ 0.000000000001,0.000000000001,0.000000000001 }  { 1,1,1 }
}

void ParticleSystem::setOffsetPos(Vector3 offset)
{
	mOffsetPos = offset;
}
void ParticleSystem::setOffsetScale(Vector3 offset)
{
	mOffsetScale = offset;
}

void ParticleSystem::setEmitting(bool stat)
{
	renderManager().setParticleEmitting(mName, stat);
}

void me::ParticleSystem::setName(std::string name)
{
	mName = name;
}

void me::ParticleSystem::setParticleName(std::string particleName)
{
	mParticleName = particleName;
}
