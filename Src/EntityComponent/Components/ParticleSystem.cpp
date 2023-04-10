#include "ParticleSystem.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "Transform.h"
#include "Utils/Vector3.h"
#include <OgreQuaternion.h>
#include <OgreVector3.h>

me::ParticleSystem::ParticleSystem(std::string name, std::string nameParticle)
{
	mName = name;
	mParticleName = nameParticle;
	renderManager().createParticle(mName, mParticleName);
}

me::ParticleSystem::~ParticleSystem()
{
	renderManager().destroyMesh(mName);
}

void me::ParticleSystem::start()
{
	mTransform = getEntity()->getComponent<Transform>("transform");
	renderManager().setParticleTransform(mName, mTransform->getPosition(), mTransform->getScale(), mTransform->getRotation());
}

void me::ParticleSystem::update()
{
	Vector3 pos = mTransform->getPosition() + mOffsetPos;
	Vector3 scale = mTransform->getScale() + mOffsetScale;
	renderManager().setParticleTransform(mName, pos, scale, mTransform->getRotation());
	//{ 0.000000000001,0.000000000001,0.000000000001 }  { 1,1,1 }
}

void me::ParticleSystem::setOffsetPos(Vector3 offset)
{
	mOffsetPos = offset;
}
void me::ParticleSystem::setOffsetScale(Vector3 offset)
{
	mOffsetScale = offset;
}

void me::ParticleSystem::setEmitting(bool stat)
{
	renderManager().setParticleEmitting(mName, stat);
}
