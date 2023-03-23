#include "MeshRenderer.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "Transform.h"
#include "Utils/Vector3.h"
#include <OgreVector3.h>

me::MeshRenderer::MeshRenderer(std::string name, std::string nameMesh)
{
	mName = name;
	mMeshName = nameMesh;
}

me::MeshRenderer::~MeshRenderer()
{
	renderManager().destroyMesh(mName);
}

void me::MeshRenderer::start()
{
	mTransform = getEntity()->getComponent<Transform>("transform");

	assert(mTransform && "An Entity doesn't have the transform component");

	renderManager().createMesh(mName, mMeshName);
	renderManager().setMeshTransform(mName, mTransform->getPosition(), mTransform->getScale(), mTransform->getRotation());
}

void me::MeshRenderer::update()
{
	if (!mStaticObject)
	{
		renderManager().setMeshTransform(mName, mTransform->getPosition(), mTransform->getScale(), mTransform->getRotation());
	}
}

void me::MeshRenderer::setStatic(bool stat)
{
	mStaticObject = stat;
}

std::string me::MeshRenderer::getName()
{
	return mName;
}


void me::MeshRenderer::setMaterial(std::string materialName)
{
	renderManager().setMeshMaterial(mName,materialName);
}

