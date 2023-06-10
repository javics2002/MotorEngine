#include "MeshRenderer.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "Transform.h"
#include "Utils/Vector3.h"

#include <cassert>

using namespace me;

MeshRenderer::MeshRenderer()
{
}


MeshRenderer::~MeshRenderer()
{
	renderManager().destroyMesh(mName);
}

bool MeshRenderer::createMesh()
{
	if (mMeshName.size() > 0) {
		return renderManager().createMesh(mName, mMeshName);;
	}

	return false;
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

void MeshRenderer::activeMesh()
{
	renderManager().activeMesh(mName);
	enabled = true;
}

void MeshRenderer::desactiveMesh()
{
	renderManager().desactiveMesh(mName);
	enabled = false;
}


void MeshRenderer::setMaterial(std::string materialName)
{
	if (materialName.size()>0)
		renderManager().setMeshMaterial(mName,materialName);
}

void MeshRenderer::setName(std::string name)
{
	mName = name;
}

void MeshRenderer::setMeshName(std::string meshName)
{
	mMeshName = meshName;
}

