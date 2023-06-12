#include "MeshRenderer.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Transform.h"
#include "Utils/Vector3.h"

#include <cassert>

using namespace me;

me::Component* me::FactoryMeshRenderer::create(Parameters& params)
{
	std::string mesh = Value(params, "mesh", std::string());
	std::string meshName = Value(params, "meshname", std::string());
	std::string materialName = Value(params, "materialname", std::string());
	bool staticState = Value(params, "staticobj", false);

	MeshRenderer* meshRenderer = new MeshRenderer();
	meshRenderer->setName(mesh);
	meshRenderer->setMeshName(meshName);
	meshRenderer->setStatic(staticState);

	if (!meshRenderer->createMesh()) {
		delete meshRenderer;
		return nullptr;
	}

	meshRenderer->setMaterial(materialName);
	return meshRenderer;
}

void me::FactoryMeshRenderer::destroy(Component* component)
{
	delete component;
}

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

	assert(mTransform);

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

