#include "InputManager.h"
#ifdef _DEBUG
#include <iostream>
#include <typeinfo>
#endif

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
	if (mButtons.count(name)) {
#ifdef _DEBUG
		std::cout << "Button " << name << " already exists.\n";
#endif

		return false;
	}

	Button button;
	button.pressed = false;

	mButtons[name] = button;

#ifdef _DEBUG
	std::cout << "Button " << name << " created.\n";
#endif

	return true;
}

bool InputManager::addButton(std::string name, Input input)
{
	return addButton(name) && addBinding(name, input);
}

bool InputManager::deleteButton(std::string name)
{
#ifdef _DEBUG
	std::cout << "Deleting button " << name << "...\n";
#endif

	for (auto it = mButtonBindings.begin(); it != mButtonBindings.end();)
		if (it->second == name)
		{
#ifdef _DEBUG
			std::cout << "Binding " << typeid(it->first.type).name() << " " << it->first.which << " deleted.\n";
#endif

			it = mButtonBindings.erase(it);
		}
		else
			it++;

#ifdef _DEBUG
	std::cout << "Button " << name << " deleted.\n";
#endif

	return mButtons.erase(name);
}

bool InputManager::addAxis(std::string name, AxisInfo info)
{
	//Axis must not exist beforehand
	if (mAxis.count(name)) {
#ifdef _DEBUG
		std::cout << "Axis " << name << " already exists.\n";
#endif

		return false;
	}

	Axis axis;
	axis.value = 0;
	axis.gravity = info.gravity;
	axis.dead = info.dead;

	mAxis[name] = axis;

#ifdef _DEBUG
	std::cout << "Axis " << name << " created.\n";
#endif

	return true;
}

bool InputManager::addAxis(std::string name, AxisInfo info, AxisInput input)
{
	return addAxis(name, info) && addBinding(name, input);
}

bool InputManager::deleteAxis(std::string name)
{
#ifdef _DEBUG
	std::cout << "Deleting button " << name << "...\n";
#endif

	for (auto it = mPositiveAxisBindings.begin(); it != mPositiveAxisBindings.end();)
		if (it->second == name) {
#ifdef _DEBUG
			std::cout << "Positive binding " << typeid(it->first.type).name() << " " << it->first.which << " deleted.\n";
#endif

			it = mPositiveAxisBindings.erase(it);
		}
		else
			it++;

	for (auto it = mNegativeAxisBindings.begin(); it != mNegativeAxisBindings.end();)
		if (it->second == name) {
#ifdef _DEBUG
			std::cout << "Negative binding " << typeid(it->first.type).name() << " " << it->first.which << " deleted.\n";
#endif

			it = mNegativeAxisBindings.erase(it);
		}
		else
			it++;

#ifdef _DEBUG
	std::cout << "Axis " << name << " deleted.\n";
#endif

	return mAxis.erase(name);
}

bool InputManager::addBinding(std::string name, Input input)
{
	mButtonBindings.insert({ input, name });

#ifdef _DEBUG
	std::cout << name << " button binded to ";
	if (input.type == SDL_EVENT_KEY_DOWN || input.type == SDL_EVENT_KEY_UP)
		std::cout << "keyboard " << SDL_GetKeyName(input.which) << ".\n";
	else if (input.type == SDL_EVENT_MOUSE_BUTTON_DOWN || input.type == SDL_EVENT_KEY_UP)
		std::cout << "mouse button " << input.which << ".\n";
	else
		std::cout << input.which << ".\n";
#endif

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

#ifdef _DEBUG
	std::cout << name << " axis binded to " << typeid(input.type).name() << " " << input.positive << 
		"positive and" << typeid(input.type).name() << " " << input.negative << " negative.\n";
#endif

	return true;
}

bool InputManager::deleteBinding(std::string name, Input input)
{
	int deletedBindings = 0;
	for (auto it = mButtonBindings.begin(); it != mButtonBindings.end();)
		if (it->second == name && it->first.type == input.type && it->first.which == input.which) {
			deletedBindings++;
			it = mButtonBindings.erase(it);

#ifdef _DEBUG
			std::cout << "Binding " << name << " to " << typeid(input.type).name() 
				<< " " << input.which << " deleted.\n";
#endif
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

#ifdef _DEBUG
	std::cout << "Binding " << name << " to " << typeid(input.type).name()
		<< " " << input.positive << " positive and " << input.negative << " negative deleted.\n";
#endif

	return deletedBindings > 0;
}

bool InputManager::getButton(std::string name)
{
	//Button must exist beforehand
	if (!mButtons.count(name)) {
#ifdef _DEBUG
		std::cout << "Button " << name << " does not exist.\n";
#endif

		return false;
	}

	return mButtons[name].pressed;
}

float InputManager::getAxis(std::string name)
{
	//Axis must exist beforehand
	if (!mAxis.count(name)) {
#ifdef _DEBUG
		std::cout << "Axis " << name << " does not exist.\n";
#endif

		return .0f;
	}

	return mAxis[name].value;
}

bool InputManager::addOnButtonPressedEvent(std::string name, int(*callback)(void*), void* additionalData)
{
	//Button must exist beforehand
	if (!mButtons.count(name)) {
#ifdef _DEBUG
		std::cout << "Button " << name << " does not exist.\n";
#endif

		return false;
	}

	/*Create filtered callback that checks if the SDL_Event source matches 
	any of the virtual button's bindings.*/
	OnButtonPressedInfo info;
	info.filter = [](void* userdata, SDL_Event* event)->int {
		OnButtonPressedInfo* info = (OnButtonPressedInfo*)userdata;

		//Get input
		Input input;
		input.type = (SDL_EventType)event->type;
		switch (input.type)
		{
		case SDL_EVENT_KEY_DOWN:
			if (event->key.repeat)
				return -1;
		case SDL_EVENT_KEY_UP:
			input.which = event->key.keysym.sym;
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		case SDL_EVENT_MOUSE_BUTTON_UP:
			input.which = event->button.button;
			break;
		//CONTROLLER TO BE IMPLEMENTED
		default:
			return -1;
		}

		//Call callback if input matches any of the virtual button's bindings.
		auto bindings = info->buttonBindings->equal_range(input);
		for (auto binding = bindings.first; binding != bindings.second; binding++)
			if (binding->second == info->buttonName)
				info->callback(info->additionalData);

		return 0;
	};

	//Store additional information needed in the filter
	info.callback = callback;
	info.additionalData = additionalData;
	info.buttonBindings = &mButtonBindings;
	info.buttonName = name;

	auto it = mOnButtonPressed.insert({ name, info });

	//Add filtered event
	addEvent(it->second.filter, &it->second);

#ifdef _DEBUG
	std::cout << "Event binded to button " << name << ".\n";
#endif

	return true;
}

bool InputManager::deleteOnButtonPressedEvent(std::string name, int(*callback)(void*), void* additionalData)
{
	//Button must have an assinged callback
	if (mOnButtonPressed.count(name) == 0) {
#ifdef _DEBUG
		std::cout << "Button " << name << " has no attached events.\n";
#endif

		return false;
	}

	//Delete callback from SDL_Event and delete its data
	auto linkedEvents = mOnButtonPressed.equal_range(name);
	for (auto info = linkedEvents.first; info != linkedEvents.second;)
		if (info->second.callback == callback && info->second.additionalData == additionalData) {
			deleteEvent(info->second.filter, &info->second);
			info = mOnButtonPressed.erase(info);
		}
		else
			info++;

	
#ifdef _DEBUG
	std::cout << "Event unbinded to button " << name << ".\n";
#endif

	return true;
}