#include "UIButton.h"

#include "EntityComponent/Entity.h"
#include "Render/RenderManager.h"
#include "UITransform.h"
#include "MotorEngine/MotorEngineError.h"
#include "MotorEngine/SceneManager.h"

using namespace me;

UIButton::UIButton()
{
}

UIButton::~UIButton()
{
}

bool UIButton::createSprite(std::string name, std::string materialName, int zOrder)
{
	mName = name;
	mSpriteName = materialName;

	if (mSpriteName.size() > 0)
		return renderManager().createSprite(mName, mSpriteName, zOrder);
}

void UIButton::start()
{
	mUITransform = getEntity()->getComponent<UITransform>("uitransform");
	if (!mUITransform){
		errorManager().throwMotorEngineError("UIButton error", "An entity doesn't have UITransform component");
        sceneManager().quit();
        return;
	}

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
