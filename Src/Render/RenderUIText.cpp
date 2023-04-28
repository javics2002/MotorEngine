#include "RenderUIText.h"
#include <OgreOverlayElement.h>
#include <OgreOverlay.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayContainer.h>
#include <OgreFontManager.h>
#include <OgreOverlayManager.h>
#include "Utils/Vector2.h"
#include "Utils/Vector4.h"
#include "Render/Window.h"

me::RenderUIText::RenderUIText(Ogre::Overlay* overlay, Ogre::TextAreaOverlayElement* panel, std::string text, int zOrder)
{
	mOverlay = overlay;
	mPanel = panel;

	mPanel->setDimensions(0.3, 0.3);
	mPanel->setCharHeight(16);
	mPanel->setMetricsMode(Ogre::GMM_PIXELS);
	mPanel->setColourTop(
		Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	mPanel->setColourBottom(
		Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	mPanel->setFontName("MyFont");
	mPanel->setCaption(text);
	mPanel->setCharHeight(4);

	Ogre::OverlayContainer* cont = dynamic_cast<Ogre::OverlayContainer*>
		(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", text));

	cont->setPosition(0.3, 0.3);
	cont->setDimensions(16, 16);

	cont->addChild(mPanel);

	overlay->add2D(cont);


	overlay->setZOrder(zOrder);
	overlay->show();
}

me::RenderUIText::~RenderUIText()
{
	mPanel->cleanupDictionary();
}

void me::RenderUIText::setTransform(Vector2 pos, Vector2 scale, float rot)
{
	mPanel->setPosition(pos.x, pos.y);
	mPanel->setDimensions(scale.x, scale.y);
	mOverlay->setRotate(Ogre::Degree(rot));
}

void me::RenderUIText::setPosition(Vector2 pos)
{
	mPanel->setPosition(pos.x, pos.y);
}

void me::RenderUIText::setScale(Vector2 scale)
{
	mPanel->setDimensions(scale.x, scale.y);
}

void me::RenderUIText::setRotation(float rot)
{
	mOverlay->setRotate(Ogre::Degree(rot));
}

void me::RenderUIText::setText(std::string text)
{
	mPanel->setCaption(text);
}

Ogre::OverlayElement* me::RenderUIText::getOgreOverlayElement()
{
	return mPanel;
}

Ogre::Overlay* me::RenderUIText::getOgreOverlay()
{
	return mOverlay;
}

void me::RenderUIText::setMaterial(std::string materialName)
{
	mPanel->setMaterialName(materialName);

}
