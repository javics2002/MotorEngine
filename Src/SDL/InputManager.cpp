#include "InputManager.h"

using namespace me;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::addEvent(SDL_EventFilter filter, void* userdata)
{
	SDL_AddEventWatch(filter, userdata);
}

void InputManager::deleteEvent(SDL_EventFilter filter, void* userdata)
{
	SDL_DelEventWatch(filter, userdata);
}

bool InputManager::addButton(std::string name)
{
	//Button must not exist beforehand
	if (mButtons.count(name))
		return false;

	Button button;
	button.pressed = false;

	mButtons[name] = button;

	return true;
}

bool InputManager::addButton(std::string name, Input input)
{
	return addButton(name) && addBinding(name, input);
}

bool InputManager::deleteButton(std::string name)
{
	for (auto it = mButtonBindings.begin(); it != mButtonBindings.end();)
		if (it->second == name)
			it = mButtonBindings.erase(it);
		else
			it++;

	return mButtons.erase(name);
}

bool InputManager::addAxis(std::string name, AxisInfo info)
{
	//Axis must not exist beforehand
	if (mAxis.count(name))
		return false;

	Axis axis;
	axis.value = 0;
	axis.gravity = info.gravity;
	axis.dead = info.dead;

	mAxis[name] = axis;

	return true;
}

bool InputManager::addAxis(std::string name, AxisInfo info, AxisInput input)
{
	return addAxis(name, info) && addBinding(name, input);
}

bool InputManager::deleteAxis(std::string name)
{
	for (auto it = mPositiveAxisBindings.begin(); it != mPositiveAxisBindings.end();)
		if (it->second == name)
			it = mPositiveAxisBindings.erase(it);
		else
			it++;

	for (auto it = mNegativeAxisBindings.begin(); it != mNegativeAxisBindings.end();)
		if (it->second == name)
			it = mNegativeAxisBindings.erase(it);
		else
			it++;

	return mAxis.erase(name);
}

bool InputManager::addBinding(std::string name, Input input)
{
	mButtonBindings.insert({ input, name });

	return true;
}

bool InputManager::addBinding(std::string name, AxisInput input)
{
	Input positive, negative;
	positive.type = negative.type = input.type;
	positive.which = input.positive;
	negative.which = input.negative;

	mPositiveAxisBindings.insert({ positive, name });
	mNegativeAxisBindings.insert({ negative, name });

	return true;
}

bool InputManager::deleteBinding(std::string name, Input input)
{
	int deletedBindings = 0;
	for (auto it = mButtonBindings.begin(); it != mButtonBindings.end();)
		if (it->second == name && it->first.type == input.type && it->first.which == input.which) {
			deletedBindings++;
			it = mButtonBindings.erase(it);
		}
		else
			it++;

	return deletedBindings > 0;
}

bool InputManager::deleteBinding(std::string name, AxisInput input)
{
	int deletedBindings = 0;
	for (auto it = mPositiveAxisBindings.begin(); it != mPositiveAxisBindings.end();)
		if (it->second == name && it->first.type == input.type && it->first.which == input.positive) {
			deletedBindings++;
			it = mPositiveAxisBindings.erase(it);
		}
		else
			it++;

	for (auto it = mNegativeAxisBindings.begin(); it != mNegativeAxisBindings.end();)
		if (it->second == name && it->first.type == input.type && it->first.which == input.negative) 
			it = mNegativeAxisBindings.erase(it);
		else
			it++;

	return deletedBindings > 0;
}

bool InputManager::getButton(std::string name)
{
	//Button must exist beforehand
	if (!mButtons.count(name))
		return false;

	return mButtons[name].pressed;
}

float InputManager::getAxis(std::string name)
{
	//Axis must exist beforehand
	if (!mAxis.count(name))
		return .0f;

	return mAxis[name].value;
}

bool InputManager::addOnButtonPressedEvent(SDL_EventFilter* filter, 
	void* userdata, std::string buttonName)
{
	//Lambda function?
	return false;
}

bool InputManager::deleteOnButtonPressedEvent(SDL_EventFilter* filter, 
	void* userdata, std::string buttonName)
{
	//Lambda function?
	return false;
}