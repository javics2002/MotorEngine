#include "UISpriteRenderer.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "UITransform.h"
#include "Utils/Vector2.h"
#include <OgreVector3.h>


me::UISpriteRenderer::UISpriteRenderer()
{
}

me::UISpriteRenderer::~UISpriteRenderer()
{
	renderManager().destroyUISprite(mName);
}

void me::UISpriteRenderer::init(std::string name, std::string nameSprite,int zOrder)
{
	mName = name;
	mSpriteName = nameSprite;
	mZOrder = zOrder;

	if (mSpriteName.size() > 0)
	{
		renderManager().createSprite(mName, mSpriteName, zOrder);
	}
}

void me::UISpriteRenderer::start()
{
	mUITransform = getEntity()->getComponent<UITransform>("uitransform");
	renderManager().setUISpriteTransform(mName, mUITransform->getPosition(), mUITransform->getScale(), mUITransform->getRotation());

}

void me::UISpriteRenderer::update(const double& dt)
{
	if (!mStaticObject)
		renderManager().setUISpriteTransform(mName, mUITransform->getPosition(), mUITransform->getScale(), mUITransform->getRotation());
}

void me::UISpriteRenderer::setStatic(bool stat)
{
	mStaticObject = stat;
}

void me::UISpriteRenderer::setZOrder(int zOrder)
{
	mZOrder = zOrder;
}

std::string me::UISpriteRenderer::getName()
{
	return mName;
}

void me::UISpriteRenderer::setSpriteMaterial(std::string materialName)
{
	renderManager().setUISpriteMaterial(mName, materialName);
}