#include "MeshRenderer.h"
#include "Ogre/OgreManager.h"
#include "Entity.h"
#include "Transform.h"
#include "Utils/Vector3.h"



me::MeshRenderer::MeshRenderer(std::string name, std::string nameMesh)
{
	mName = name;
	mMeshName = nameMesh;

}

me::MeshRenderer::~MeshRenderer()
{
}

void me::MeshRenderer::start()
{
	mTransform = getEntity()->getComponent<Transform>("transform");
	om().createMesh(mName, mMeshName);
	om().setMeshTransform(mName, mTransform->getPosition().v3ToOgreV3(), mTransform->getScale().v3ToOgreV3(), mTransform->getRotation());

}

void me::MeshRenderer::update()
{
	if (!mStaticObject)
	{
		om().setMeshTransform(mName, mTransform->getPosition().v3ToOgreV3(), mTransform->getScale().v3ToOgreV3(), mTransform->getRotation());
	}
}

void me::MeshRenderer::setStatic(bool stat)
{
	mStaticObject = stat;
}

