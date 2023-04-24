#include "UIText.h"
#include "Render/RenderManager.h"
#include <OgreOverlay.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include "UIElement.h"
#include <OgreTextAreaOverlayElement.h>

me::UIText::UIText(std::string name, std::string fontName, float posX, float posY, float width, float height, std::string text, Vector4 textColor) : UIElement()
{
	mTextArea = static_cast<Ogre::TextAreaOverlayElement*>(mOverlayManager->createOverlayElement("TextArea", name + std::to_string(mElems)));
	mOverlay = mOverlayManager->create(name + std::to_string(mElems));

	setPosition(posX, posY);
	setFont(fontName);
	setSize(width, height);
	setText(text);
	setTextColor(textColor);
	setTextAligment(Ogre::TextAreaOverlayElement::Alignment::Center);
	setWidth(width);
	setHeight(height);

	mOverlay->add2D((Ogre::OverlayContainer*)mTextArea);
}

me::UIText::~UIText()
{
}

void me::UIText::setPosition(float x, float y)
{
	// Set the position 
	mTextArea->setPosition(x, y);
}

void me::UIText::setSize(float w, float h)
{
	// Set the dimensions and char height
	mTextArea->setDimensions(w, h);
	mTextArea->setCharHeight(h);
}

void me::UIText::setFont(std::string fontName)
{
	// Set the font 
	mTextArea->setFontName(fontName);
}

void me::UIText::setText(std::string text)
{
	// Set the caption
	mTextArea->setCaption(text);
}

void me::UIText::setTextColor(Vector4 newColor)
{
	// Set the color
	mTextArea->setColour(Ogre::ColourValue(newColor.x, newColor.y, newColor.z, newColor.w));
}


void me::UIText::setWidth(double widthValue)
{
	// Set the width
	mTextArea->setWidth(widthValue);
}

void me::UIText::setHeight(double heightValue)
{
	// Set the height
	mTextArea->setHeight(heightValue);
}

void me::UIText::setActive(bool active)
{
	// Show or hide the text area 
	if (active) mTextArea->show();
	else mTextArea->hide();
}

void me::UIText::setTextAligment(int a)
{
	Ogre::TextAreaOverlayElement::Alignment aa = static_cast<Ogre::TextAreaOverlayElement::Alignment>(a);
	mTextArea->setAlignment(aa);
}
