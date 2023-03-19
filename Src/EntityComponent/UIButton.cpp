#include "UIButton.h"
#include "Input/InputManager.h"
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>


me::UIButton::UIButton(std::string name, float width, float height, float left, float top)
{
	mButtonArea = static_cast<Ogre::TextAreaOverlayElement*>(mOverlayManager->createOverlayElement("TextArea", name + std::to_string(mElems)));
	mOverlay = mOverlayManager->create(name + std::to_string(mElems));

	setTop(top);
	setLeft(left);
	setSize(Vector2(width,height));
	setWidth(width);
	setHeight(height);

	mInteractive = true;

	mOverlay->add2D((Ogre::OverlayContainer*)mButtonArea);
}

me::UIButton::~UIButton()
{
}

void me::UIButton::update()
{
	if (mInteractive) handleInput();
}

void me::UIButton::handleInput()
{
	Vector2 mousePosition = im().getMousePositon();
	if (mFocus && mousePosition.x >= getPos().x && mousePosition.x <= getPos().x + getSize().x &&
		mousePosition.y >= getPos().y && mousePosition.y <= getPos().y + getSize().y) {
		if (im().justClicked()) {
			for (auto l : mLambda) l();
		}
	}
}

void me::UIButton::onClick(std::function<void()> l)
{
	mLambda.push_back(l);
}
