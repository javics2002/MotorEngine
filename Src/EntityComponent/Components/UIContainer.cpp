#include "UIContainer.h"

using namespace me;

void UIContainer::addElement(Component* element)
{
	UIElement* ui;

	if (ui=static_cast<UIElement*>(element)) {
		//ui->mContainer = this;

		mUIChild m = mUIChild();
		//m.mPos = ui->getPosition();
		m.mScale = ui->getSize();
		m.mUiElement = ui;

		mUiElements.push_back(m);
	}

}

