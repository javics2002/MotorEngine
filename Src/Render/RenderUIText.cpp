#include "RenderUIText.h"
#include <OgreOverlay.h>
#include <OgreOverlayElement.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>

#include "Render/RenderManager.h"

using namespace me;

RenderUIText::RenderUIText(std::string name, std::string text, int zOrder, std::string fontName)
{	
	mOverlay = renderManager().getOgreManager()->create(name + "Overlay");

	mOverlay->setZOrder(zOrder);

	mCont = static_cast<Ogre::OverlayContainer*>(
		renderManager().getOgreManager()->createOverlayElement("Panel", "myPanel" + name));

	mOverlay->add2D(mCont);

	mTextArea = static_cast<Ogre::TextAreaOverlayElement*>(
		renderManager().getOgreManager()->createOverlayElement("TextArea", "myTextArea" + name));

	mTextArea->setMetricsMode(Ogre::GMM_RELATIVE);
	mTextArea->setFontName(fontName);
	mTextArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
	mCont->addChild(mTextArea);
	mOverlay->show();

}

RenderUIText::~RenderUIText()
{
	mOverlay->remove2D(mCont);
	mCont->removeChild(mTextArea->getName());
	renderManager().getOgreManager()->destroyOverlayElement(mTextArea);
	renderManager().getOgreManager()->destroyOverlayElement(mCont);
	renderManager().getOgreManager()->destroy(mOverlay);
}

void RenderUIText::setTransform(Vector2 pos, Vector2 scale, float rot)
{
	mTextArea->setPosition(pos.x, pos.y);
	mTextArea->setDimensions(scale.x, scale.y);
	mOverlay->setRotate(Ogre::Degree(rot));
}

void RenderUIText::setPosition(Vector2 pos)
{
	mTextArea->setPosition(pos.x, pos.y);
}

void RenderUIText::setDimensions(Vector2 scale)
{
	mTextArea->setDimensions(scale.x, scale.y);
}

void RenderUIText::setRotation(float rot)
{
	mOverlay->setRotate(Ogre::Degree(rot));
}

void RenderUIText::setText(std::string text)
{
	mTextArea->setCaption(text);
}

void me::RenderUIText::setFont(std::string fontName)
{
	mTextArea->setFontName(fontName);
}

void me::RenderUIText::setCharHeight(float charHeight)
{
	mTextArea->setCharHeight(charHeight);
}

void me::RenderUIText::setColour(Vector3 colour)
{
	mTextArea->setColour(Ogre::ColourValue(colour.x, colour.y, colour.z));
}

void me::RenderUIText::setColourBottom(Vector3 colour)
{
	mTextArea->setColourBottom(Ogre::ColourValue(colour.x, colour.y, colour.z));
}

void me::RenderUIText::setColourTop(Vector3 colour)
{
	mTextArea->setColourTop(Ogre::ColourValue(colour.x, colour.y, colour.z));
}

void RenderUIText::setMaterial(std::string materialName)
{
	mTextArea->setMaterialName(materialName);
}

void RenderUIText::setActive(bool active)
{
	mTextArea->setVisible(active);
}

Ogre::OverlayElement* RenderUIText::getOgreOverlayElement()
{
	return mTextArea;
}

Ogre::Overlay* RenderUIText::getOgreOverlay()
{
	return mOverlay;
}

