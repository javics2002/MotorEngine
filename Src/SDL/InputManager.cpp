#include "InputManager.h"

using namespace me;

InputManager::InputManager()
{
	mButtons = std::vector<Button>(M_INITIAL_BUTTONS);
	mButtonsSize = 0;
}

InputManager::~InputManager()
{
}
