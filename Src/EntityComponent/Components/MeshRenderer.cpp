#include "MeshRenderer.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "Transform.h"
#include "Utils/Vector3.h"
#include <OgreVector3.h>

using namespace me;

MeshRenderer::MeshRenderer(std::string name, std::string nameMesh)
{
	mName = name;
	mMeshName = nameMesh;
}


MeshRenderer::~MeshRenderer()
{
	renderManager().destroyMesh(mName);
}

void MeshRenderer::init()
{
	if (mMeshName.size() > 0)
		renderManager().createMesh(mName, mMeshName);
}

void MeshRenderer::start()
{
	mTransform = getEntity()->getComponent<Transform>("transform");

	assert(mTransform && "An Entity doesn't have the transform component");

	renderManager().setMeshTransform(mName, mTransform->getPosition(), mTransform->getScale(), mTransform->getRotation());
}

void MeshRenderer::update(const double& dt)
{
	if (!mStaticObject)
		renderManager().setMeshTransform(mName, mTransform->getPosition(), mTransform->getScale(), mTransform->getRotation());
}

void MeshRenderer::setStatic(bool stat)
{
	mStaticObject = stat;
}

std::string MeshRenderer::getName()
{
	return mName;
}


void MeshRenderer::setMaterial(std::string materialName)
{
	renderManager().setMeshMaterial(mName,materialName);
}

