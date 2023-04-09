#include "RenderUISprite.h"
#include <OgreOverlayElement.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>

#include "Utils/Vector2.h"
#include "Render/Window.h"

me::RenderUISprite::RenderUISprite(Ogre::Overlay* overlay, Ogre::OverlayElement* panel, std::string spriteMaterialName)
{
	mOverlay = overlay;
	mPanel = panel;

	mPanel->setPosition(.1, .1);
	panel->setDimensions(.1, .1);
	panel->setMaterialName(spriteMaterialName);

	overlay->add2D(dynamic_cast<Ogre::OverlayContainer*>(panel));
	overlay->setZOrder(10);
	overlay->show();
}

me::RenderUISprite::~RenderUISprite()
{
	mPanel->cleanupDictionary();
}

void me::RenderUISprite::setTransform(Vector2 pos, Vector2 scale, float rot)
{
	mPanel->setPosition(pos.x, pos.y);
	mPanel->setDimensions(scale.x, scale.y);
	mOverlay->setRotate(Ogre::Degree(rot));
}

void me::RenderUISprite::setPosition(Vector2 pos)
{
	mPanel->setPosition(pos.x, pos.y);
}

void me::RenderUISprite::setScale(Vector2 scale)
{
	mPanel->setDimensions(scale.x, scale.y);
}

void me::RenderUISprite::setRotation(float rot)
{
	mOverlay->setRotate(Ogre::Degree(rot));
}

Ogre::OverlayElement* me::RenderUISprite::getOgreOverlayElement()
{
	return mPanel;
}

Ogre::Overlay* me::RenderUISprite::getOgreOverlay()
{
	return mOverlay;
}

void me::RenderUISprite::setMaterial(std::string materialName)
{
	mMaterialName = materialName;
	mPanel->setMaterialName(materialName);

}
