#include "RenderUIText.h"
#include <OgreOverlay.h>
#include <OgreOverlayElement.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include "Utils/Vector2.h"
#include "Utils/Vector4.h"

using namespace me;

RenderUIText::RenderUIText(std::string name, std::string text, int zOrder,
	float positionX, float positionY, float dimensionX, float dimensionY, 
	std::string fontName, float charHeight, Vector3 color)
{	

	mOverlay = Ogre::OverlayManager::getSingleton().create(name + "Overlay");

	mCont = static_cast<Ogre::OverlayContainer*>(
		Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "myPanel" + name));

	mOverlay->add2D(mCont);

	mTextArea = static_cast<Ogre::TextAreaOverlayElement*>(
		Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "myTextArea" + name));


	mTextArea->initialise();
	mTextArea->setMetricsMode(Ogre::GMM_PIXELS);
	mTextArea->setPosition(positionX, positionY); // Posición en píxeles
	mTextArea->setDimensions(dimensionX, dimensionY); // Ancho y alto en píxeles
	mTextArea->setFontName(fontName);
	mTextArea->setCharHeight(charHeight);
	mTextArea->setColour(Ogre::ColourValue(color.x,color.y,color.z));
	mTextArea->setCaption(text);

	mCont->addChild(mTextArea);
	mOverlay->show();
}

RenderUIText::~RenderUIText()
{
	mTextArea->setVisible(false);
	mTextArea->cleanupDictionary();
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

