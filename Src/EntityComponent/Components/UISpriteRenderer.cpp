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

void me::UISpriteRenderer::init(std::string name, std::string nameSprite)
{
	mName = name;
	mSpriteName = nameSprite;

	if (mSpriteName.size() > 0)
	{
		renderManager().createSprite(mName, mSpriteName);
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

std::string me::UISpriteRenderer::getName()
{
	return mName;
}

void me::UISpriteRenderer::setSpriteMaterial(std::string materialName)
{
	renderManager().setUISpriteMaterial(mName, materialName);
}