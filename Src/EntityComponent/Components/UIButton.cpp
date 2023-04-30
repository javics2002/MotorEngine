#include "UIButton.h"
#include "Input/InputManager.h"
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include "EntityComponent/Entity.h"
#include "Render/RenderManager.h"
#include "UITransform.h"

using namespace me;

UIButton::UIButton()
{
}

UIButton::~UIButton()
{
}

void UIButton::init(std::string name, std::string materialName, int zOrder)
{
	mName = name;
	mSpriteName = materialName;

	if (mSpriteName.size() > 0)
	{
		renderManager().createSprite(mName, mSpriteName, zOrder);
	}

}

void UIButton::start()
{
	mUITransform = getEntity()->getComponent<UITransform>("uitransform");
	renderManager().setUISpriteTransform(mName, mUITransform->getPosition(), mUITransform->getScale(), mUITransform->getRotation());
}

std::string UIButton::getName()
{
	return mName;
}

void UIButton::setSpriteMaterial(std::string materialName)
{
	renderManager().setUISpriteMaterial(mName, materialName);
}
