#pragma once
#ifndef __ENTITYCOMPONENT_UICONTAINER
#define __ENTITYCOMPONENT_UICONTAINER

#include "UIElement.h"
#include "Utils/Vector3.h"
#include "Utils/Vector2.h"
#include <vector>

namespace me {
	class __MOTORENGINE_API UIContainer : public UIElement
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
}
#endif