#include "RenderUISprite.h"
#include <OgreOverlayElement.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>

#include "Render/Window.h"

using namespace me;

RenderUISprite::RenderUISprite(Ogre::Overlay* overlay, Ogre::OverlayElement* panel, std::string spriteMaterialName, int zOrder)
{
	mOverlay = overlay;
	mPanel = panel;

	mMaterialName = spriteMaterialName;

	panel->setMaterialName(spriteMaterialName);

	overlay->add2D(dynamic_cast<Ogre::OverlayContainer*>(panel));
	overlay->setZOrder(zOrder);
	overlay->show();
}

RenderUISprite::~RenderUISprite()
{
	mPanel->cleanupDictionary();
}

void RenderUISprite::setTransform(Vector2 pos, Vector2 scale, float rot)
{
	mPanel->setPosition(pos.x, pos.y);
	mPanel->setDimensions(scale.x, scale.y);
	mOverlay->setRotate(Ogre::Degree(rot));
}

void RenderUISprite::setPosition(Vector2 pos)
{
	mPanel->setPosition(pos.x, pos.y);
}

void RenderUISprite::setScale(Vector2 scale)
{
	mPanel->setDimensions(scale.x, scale.y);
}

void RenderUISprite::setRotation(float rot)
{
	mOverlay->setRotate(Ogre::Degree(rot));
}

Ogre::OverlayElement* RenderUISprite::getOgreOverlayElement()
{
	return mPanel;
}

Ogre::Overlay* RenderUISprite::getOgreOverlay()
{
	return mOverlay;
}

void RenderUISprite::setMaterial(std::string materialName)
{
	mMaterialName = materialName;
	mPanel->setMaterialName(materialName);
}
