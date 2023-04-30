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

using namespace me;

RenderUIText::RenderUIText(Ogre::Overlay* overlay, Ogre::TextAreaOverlayElement* panel, std::string text, int zOrder)
{
	/*mOverlay = overlay;
	mPanel = panel;

	mPanel->setDimensions(width, height);
	mPanel->setCharHeight(charHeight);
	mPanel->setMetricsMode(Ogre::GMM_PIXELS);
	mPanel->setColourTop(Ogre::ColourValue(colourTop.x, colourTop.y, colourTop.z));
	mPanel->setColourBottom(Ogre::ColourValue(colourBottom.x, colourBottom.y, colourBottom.z));
	mPanel->setFontName(fontName);
	mPanel->setCaption(text);

	Ogre::OverlayContainer* cont = dynamic_cast<Ogre::OverlayContainer*>
		(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Text_" + text, text));

	cont->setPosition(0.3, 0.3);
	cont->setDimensions(16, 16);

	cont->addChild(mPanel);

	overlay->add2D(cont);

	overlay->setZOrder(zOrder);
	overlay->show();*/

	//Cosas de la IA BORRAR
	/*
	// Obtén una referencia al `OverlayManager`
	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

	// Crea un `Overlay` con un único `Panel`
	Ogre::Overlay* overlay = overlayManager.create("myOverlay");
	Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "myPanel"));
	overlay->add2D(panel);

	// Crea un `TextAreaOverlayElement` y configúralo
	Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
		overlayManager.createOverlayElement("TextArea", "myTextArea"));
	textArea->initialise();
	textArea->setMetricsMode(Ogre::GMM_PIXELS);
	textArea->setPosition(10, 10); // Posición en píxeles
	textArea->setDimensions(200, 50); // Ancho y alto en píxeles
	textArea->setFontName("Mario");
	textArea->setCharHeight(50);
	textArea->setColour(Ogre::ColourValue::White);
	textArea->setCaption("lap 1/3    00:24.958");

	// Añade el `TextAreaOverlayElement` al `Panel` y muestra el `Overlay`
	panel->addChild(textArea);
	overlay->show();*/
}

RenderUIText::~RenderUIText()
{
	mPanel->cleanupDictionary();
}

void RenderUIText::setTransform(Vector2 pos, Vector2 scale, float rot)
{
	mPanel->setPosition(pos.x, pos.y);
	mPanel->setDimensions(scale.x, scale.y);
	mOverlay->setRotate(Ogre::Degree(rot));
}

void RenderUIText::setPosition(Vector2 pos)
{
	mPanel->setPosition(pos.x, pos.y);
}

void RenderUIText::setScale(Vector2 scale)
{
	mPanel->setDimensions(scale.x, scale.y);
}

void RenderUIText::setRotation(float rot)
{
	mOverlay->setRotate(Ogre::Degree(rot));
}

void RenderUIText::setText(std::string text)
{
	mPanel->setCaption(text);
}

Ogre::OverlayElement* RenderUIText::getOgreOverlayElement()
{
	return mPanel;
}

Ogre::Overlay* RenderUIText::getOgreOverlay()
{
	return mOverlay;
}

void RenderUIText::setMaterial(std::string materialName)
{
	mPanel->setMaterialName(materialName);
}
