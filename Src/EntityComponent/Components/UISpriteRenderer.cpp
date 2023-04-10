#include "UISpriteRenderer.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "UITransform.h"
#include "Utils/Vector2.h"
#include <OgreVector3.h>

me::UISpriteRenderer::UISpriteRenderer(std::string name, std::string nameSprite)
{
	mName = name;
	mSpriteName = nameSprite;
}

me::UISpriteRenderer::UISpriteRenderer()
{
}

me::UISpriteRenderer::~UISpriteRenderer()
{
	renderManager().destroyMesh(mName);
}

void me::UISpriteRenderer::init(std::string name, std::string nameSprite)
{
	mName = name;
	mSpriteName = nameSprite;
	if (mSpriteName.size() > 0)
	{
		renderManager().createSprite(mName, mSpriteName);
		renderManager().setUISpriteTransform(mName, mUITransform->getPosition(), mUITransform->getScale(), mUITransform->getRotation());
	}
}

void me::UISpriteRenderer::start()
{
	mUITransform = getEntity()->getComponent<UITransform>("uitransform");

	assert(mUITransform && "An Entity doesn't have the UITransform component");
	if (mSpriteName.size() > 0)
	{
		renderManager().createSprite(mName, mSpriteName);
		renderManager().setUISpriteTransform(mName, mUITransform->getPosition(), mUITransform->getScale(), mUITransform->getRotation());
	}
}

void me::UISpriteRenderer::update()
{
	if (!mStaticObject)
	{
		renderManager().setUISpriteTransform(mName, mUITransform->getPosition(), mUITransform->getScale(), mUITransform->getRotation());
	}
}

void me::UISpriteRenderer::setStatic(bool stat)
{
	mStaticObject = stat;
}

std::string me::UISpriteRenderer::getName()
{
	return mName;
}

void me::UISpriteRenderer::setSpriteMaterial(std::string materialName)
{
	renderManager().setUISpriteMaterial(mName, materialName);
}