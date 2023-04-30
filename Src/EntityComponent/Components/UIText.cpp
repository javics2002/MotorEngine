#include "UIText.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "UITransform.h"

using namespace me;

UIText::UIText() : Component()
{
}

UIText::~UIText()
{
}

void UIText::init(std::string name, std::string text, int zOrder)
{
	mName = name;
	mZOrder = zOrder;

	if (text.size() > 0)
		renderManager().createText(mName, text, zOrder);
 }

void UIText::start()
{
	mUITransform = getEntity()->getComponent<UITransform>("uitransform");
	renderManager().setUITextTransform(mName, mUITransform->getPosition(), 
		mUITransform->getScale(), mUITransform->getRotation());
}

void UIText::setPosition(float x, float y)
{
	// Set the position 
	
}

void UIText::setSize(float w, float h)
{
	// Set the dimensions and char height
	
}

void UIText::setFont(std::string fontName)
{
	// Set the font 
	
}

void UIText::setText(std::string text)
{
	// Set the caption
	
}

void UIText::setTextColor(Vector4 newColor)
{
	// Set the color
	
}


void UIText::setWidth(double widthValue)
{
	// Set the width
	
}

void UIText::setHeight(double heightValue)
{
	// Set the height
	
}

void UIText::setActive(bool active)
{
	// Show or hide the text area 
	
}

