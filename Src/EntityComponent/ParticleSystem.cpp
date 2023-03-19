#include "ParticleSystem.h"
#include "Render/OgreManager.h"
#include "Entity.h"
#include "Transform.h"
#include "Utils/Vector3.h"
#include <OgreQuaternion.h>
#include <OgreVector3.h>

me::ParticleSystem::ParticleSystem(std::string name, std::string nameParticle)
{
	mName = name;
	mParticleName = nameParticle;

}

me::ParticleSystem::~ParticleSystem()
{
	om().destroyMesh(mName);
}

void me::ParticleSystem::start()
{
	mTransform = getEntity()->getComponent<Transform>("transform");
	om().createParticle(mName, mParticleName);
	om().setParticleTransform(mName, mTransform->getPosition().v3ToOgreV3(), mTransform->getScale().v3ToOgreV3(), mTransform->getRotation());

}

void me::ParticleSystem::update()
{
	Vector3 pos = mTransform->getPosition() + mOffsetPos;
	Vector3 scale = mTransform->getScale() + mOffsetScale;
	om().setParticleTransform(mName, pos.v3ToOgreV3(), scale.v3ToOgreV3(), mTransform->getRotation());

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
	om().setParticleEmitting(mName, stat);
}
