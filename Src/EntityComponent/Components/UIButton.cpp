#include "UIButton.h"
#include "Input/InputManager.h"
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>

using namespace me;

UIButton::UIButton(std::string name, float width, float height, float left, float top)
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

UIButton::~UIButton()
{
}

void UIButton::update(const double& dt)
{
	if (mInteractive) handleInput(dt);
}

void UIButton::handleInput(const double& dt)
{
	Vector2 mousePosition = inputManager().getMousePositon();
	if (mFocus && mousePosition.x >= getPos().x && mousePosition.x <= getPos().x + getSize().x &&
		mousePosition.y >= getPos().y && mousePosition.y <= getPos().y + getSize().y) {
		/*if (inputManager().justClicked()) {
			for (auto l : mLambda) l();
		}*/
	}
}



void UIButton::onClick(std::function<void()> l)
{
	mLambda.push_back(l);
}
