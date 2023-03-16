#include "UIElement.h"
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>

me::UIElement::UIElement()
{
    mOverlayManager = Ogre::OverlayManager::getSingletonPtr();
    mElems++;
}

me::UIElement::~UIElement()
{
    mOverlayManager->destroy(mOverlay);
}

void me::UIElement::show()
{
    mOverlay->show();
}

void me::UIElement::hide()
{
    mOverlay->hide();
}

Vector2 me::UIElement::getSize()
{
    return Vector2(mOverlayContainer->getWidth(), mOverlayContainer->getHeight());
}

Vector2 me::UIElement::getPos()
{
    return Vector2(mOverlayContainer->getLeft(), mOverlayContainer->getTop());
}

void me::UIElement::setSize(Vector2 size)
{
    mOverlayContainer->setDimensions(size.x,size.y);
}

bool me::UIElement::isVisible()
{
    return mOverlay->isVisible();
}

void me::UIElement::setTop(float top)
{
    mOverlayContainer->setTop(top);
}

void me::UIElement::setLeft(float left)
{
    mOverlayContainer->setLeft(left);
}

void me::UIElement::setWidth(float wifth)
{
    mOverlayContainer->setWidth(wifth);
}

void me::UIElement::setHeight(float height)
{
    mOverlayContainer->setHeight(height);
}

void me::UIElement::setInteractive(bool interactive)
{
    mInteractive = interactive;
}

void me::UIElement::setFocusNow(bool focus)
{
    mFocus = focus;
}

bool me::UIElement::getIsInteractive()
{
    return mInteractive;
}

bool me::UIElement::getIsFocusNow()
{
    return mFocus;
}

