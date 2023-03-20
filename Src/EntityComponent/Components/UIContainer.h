#pragma once
#ifndef __EC_UI_CONTAINER
#define __EC_UI_CONTAINER

#include "UIElement.h"
#include "Utils/Vector3.h"
#include "Utils/Vector2.h"

#include <vector>

class UIContainer : public me::UIElement
{
public:

	void addElement(Component* c);

private:

	struct mUIChild {
		UIElement* mUiElement;
		me::Vector3 mPos;
		Vector2 mScale;
	};
	std::vector<mUIChild> mUiElements;


};


#endif // !1

