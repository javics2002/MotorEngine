#include "UIElement.h"
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>

using namespace me;

UIElement::UIElement()
{
    mOverlayManager = Ogre::OverlayManager::getSingletonPtr();
    mElems++;
}

UIElement::~UIElement()
{
    mOverlayManager->destroy(mOverlay);
}

void UIElement::show()
{
    mOverlay->show();
}

void UIElement::hide()
{
    mOverlay->hide();
}

Vector2 UIElement::getSize()
{
    return Vector2(mOverlayContainer->getWidth(), mOverlayContainer->getHeight());
}

Vector2 UIElement::getPos()
{
    return Vector2(mOverlayContainer->getLeft(), mOverlayContainer->getTop());
}

void UIElement::setSize(Vector2 size)
{
    mOverlayContainer->setDimensions(size.x,size.y);
}

bool UIElement::isVisible()
{
    return mOverlay->isVisible();
}

void UIElement::setTop(float top)
{
    mOverlayContainer->setTop(top);
}

void UIElement::setLeft(float left)
{
    mOverlayContainer->setLeft(left);
}

void UIElement::setWidth(float wifth)
{
    mOverlayContainer->setWidth(wifth);
}

void UIElement::setHeight(float height)
{
    mOverlayContainer->setHeight(height);
}

void UIElement::setInteractive(bool interactive)
{
    mInteractive = interactive;
}

void UIElement::setFocusNow(bool focus)
{
    mFocus = focus;
}

bool UIElement::getIsInteractive()
{
    return mInteractive;
}

bool UIElement::getIsFocusNow()
{
    return mFocus;
}

