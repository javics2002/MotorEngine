#include "UISpriteRenderer.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "UITransform.h"
#include "Utils/Vector2.h"
#include <OgreVector3.h>



me::Component* me::FactoryUISpriteRenderer::create(Parameters& params)
{
	if (params.empty())
		return new UISpriteRenderer();

	std::string sprite = Value(params, "sprite", std::string());
	std::string materialName = Value(params, "materialname", std::string());
	int zOrder = Value(params, "zorder", 1);
	bool staticState = Value(params, "staticobj", false);

	UISpriteRenderer* spriteRenderer = new UISpriteRenderer();
	if (!spriteRenderer->createSprite(sprite, materialName, zOrder)) {
		delete spriteRenderer;
		return nullptr;
	}
	spriteRenderer->setStatic(staticState);

	return spriteRenderer;
}

void me::FactoryUISpriteRenderer::destroy(Component* component)
{
	delete component;
}


me::UISpriteRenderer::UISpriteRenderer()
{
}

me::UISpriteRenderer::~UISpriteRenderer()
{
	renderManager().destroyUISprite(mName);
}

bool me::UISpriteRenderer::createSprite(std::string name, std::string nameSprite,int zOrder)
{
	mName = name;
	mSpriteName = nameSprite;
	mZOrder = zOrder;

	if (mSpriteName.size() > 0)
		return renderManager().createSprite(mName, mSpriteName, zOrder);

	return false;
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

void me::UISpriteRenderer::resetSpriteMaterial()
{
	setSpriteMaterial(mSpriteName);
}

std::string me::UISpriteRenderer::getName()
{
	return mName;
}

void me::UISpriteRenderer::setSpriteMaterial(std::string materialName)
{
	renderManager().setUISpriteMaterial(mName, materialName);
}