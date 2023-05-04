#include "UIText.h"
#include "Render/RenderUIText.h"
#include "EntityComponent/Entity.h"
#include "UITransform.h"

using namespace me;

UIText::UIText() : Component()
{
}

UIText::~UIText()
{
	delete mRenderUIText;
}

void UIText::init(std::string name, std::string text, int zOrder,std::string fontName)
{
	mName = name;
	mZOrder = zOrder;

	if (text.size() > 0)
		 mRenderUIText = new RenderUIText(mName, text, zOrder,
			fontName);
 }

void UIText::start()
{
	mUITransform = getEntity()->getComponent<UITransform>("uitransform");
}

void UIText::setPosition(float x, float y)
{
	mRenderUIText->setPosition(Vector2( x,y ));
	
}

void UIText::setSize(float w, float h)
{
	mRenderUIText->setDimensions(Vector2( w,h ));
	
}

void UIText::setFont(std::string fontName)
{
	mRenderUIText->setFont(fontName);
	
}

void UIText::setText(std::string text)
{
	mRenderUIText->setText(text);
	
}

void UIText::setColour(Vector3 newColor)
{
	mRenderUIText->setColour(newColor);
	
}

void me::UIText::setColourBottom(Vector3 newColor)
{
	mRenderUIText->setColourBottom(newColor);
}

void me::UIText::setColourTop(Vector3 newColor)
{
	mRenderUIText->setColourTop(newColor);
}

void UIText::setCharHeight(double heightValue)
{
	mRenderUIText->setCharHeight(heightValue);
	
}

void UIText::setActive(bool active)
{
	// Show or hide the text area 
	mRenderUIText->setActive(active);
}

