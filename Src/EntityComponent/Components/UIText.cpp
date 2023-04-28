#include "UIText.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "UITransform.h"

me::UIText::UIText() : me::Component()
{

}

me::UIText::~UIText()
{
}


void me::UIText::init(std::string name, std::string text, int zOrder)
{
	mName = name;
	mZOrder = zOrder;

	if (text.size() > 0)
	{
		renderManager().createText(mName, text, zOrder);
	}
 }



void me::UIText::start()
{
	mUITransform = getEntity()->getComponent<UITransform>("uitransform");
	renderManager().setUITextTransform(mName, mUITransform->getPosition(), mUITransform->getScale(), mUITransform->getRotation());
}



void me::UIText::setPosition(float x, float y)
{
	// Set the position 
	
}

void me::UIText::setSize(float w, float h)
{
	// Set the dimensions and char height
	
}

void me::UIText::setFont(std::string fontName)
{
	// Set the font 
	
}

void me::UIText::setText(std::string text)
{
	// Set the caption
	
}

void me::UIText::setTextColor(Vector4 newColor)
{
	// Set the color
	
}


void me::UIText::setWidth(double widthValue)
{
	// Set the width
	
}

void me::UIText::setHeight(double heightValue)
{
	// Set the height
	
}

void me::UIText::setActive(bool active)
{
	// Show or hide the text area 
	
}

