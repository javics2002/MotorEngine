#include "ParticleSystem.h"

#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Transform.h"
#include "MotorEngine/MotorEngineError.h"
#include "Utils/Vector3.h"
#include <OgreQuaternion.h>
#include <OgreVector3.h>

using namespace me;

me::Component* me::FactoryParticleSystem::create(Parameters& params)
{
	ParticleSystem* particleSystem = new ParticleSystem();

	std::string particle = Value(params, "particle", std::string());
	std::string particleName = Value(params, "particlename", std::string());
	bool emitted = Value(params, "emitted", false);

	particleSystem->setName(particle);
	particleSystem->setParticleName(particleName);
	particleSystem->setOffsetPos(Vector3(Value(params, "offpos_x", 0.0f),
		Value(params, "offpos_y", 0.0f), Value(params, "offpos_z", 0.0f)));
	particleSystem->setOffsetScale(Vector3(Value(params, "offscale_x", 0.0f),
		Value(params, "offscale_y", 0.0f), Value(params, "offscale_z", 0.0f)));

	if(!particleSystem->setContext()) return nullptr;

	particleSystem->setEmitting(emitted);
	return particleSystem;
}

void me::FactoryParticleSystem::destroy(Component* component)
{
	delete component;
}

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

bool ParticleSystem::setContext()
{
	if (mName.size() > 0)
		return renderManager().createParticle(mName, mParticleName);
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