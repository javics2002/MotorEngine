#include "InputManager.h"
#ifdef _DEBUG
#include <iostream>
#include <typeinfo>
#endif
#define EVENT_BUTTON_DOWN event->type == SDL_EVENT_KEY_DOWN || \
	event->type == SDL_EVENT_MOUSE_BUTTON_DOWN || \
	event->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN
#define EVENT_BUTTON_UP event->type == SDL_EVENT_KEY_UP || \
	event->type == SDL_EVENT_MOUSE_BUTTON_UP || \
	event->type == SDL_EVENT_GAMEPAD_BUTTON_UP

using namespace me;

InputManager::InputManager()
{
	SDL_AddEventWatch(watchControllers, NULL);
	SDL_AddEventWatch(updateInputData, NULL);
}

InputManager::~InputManager()
{
}

bool me::InputManager::justClicked()
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

bool InputManager::addButton(std::string name, int player)
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
	button.player = player;

	mButtons[name] = button;

#ifdef _DEBUG
	std::cout << "Button " << name << " created.\n";
#endif

	return true;
}

bool InputManager::addButton(std::string name, Input input, int player)
{
	return addButton(name, player) && addBinding(name, input);
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

#ifdef _DEBUG
void printInputDevice(Input input) {
	switch (input.type)
	{
	case INPUTTYPE_KEYBOARD:
		std::cout << "keyboard " << SDL_GetKeyName(input.which);
		break;
	case INPUTTYPE_MOUSE_CLICK:
		std::cout << "mouse button " << input.which;
		break;
	case INPUTTYPE_GAMEPAD_BUTTON:
		std::cout << "gamepad button " << input.which;
		break;
	default:
		std::cout << input.which;
		break;
	}
}
#endif

bool InputManager::addBinding(std::string name, Input input)
{
	mButtonBindings.insert({ input, name });

#ifdef _DEBUG
	std::cout << name << " button binded to ";
	printInputDevice(input);
	std::cout << ".\n";
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
	std::cout << name << " axis binded to ";
	printInputDevice({ input.type, input.positive });
	std::cout << " positive and ";
	printInputDevice({ input.type, input.negative });
	std::cout << " negative.\n";
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

	if (std::abs(mAxis[name].value) >= mAxis[name].dead)
		return mAxis[name].value;
	else
		return 0;
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
		if (EVENT_BUTTON_UP)
			return 0;

		OnButtonPressedInfo* info = (OnButtonPressedInfo*)userdata;

		//Call callback if input matches any of the virtual button's bindings.
		auto bindings = info->buttonBindings->equal_range(getInput(event));
		for (auto binding = bindings.first; binding != bindings.second; binding++)
			if (binding->second == info->buttonName 
				&& (info->player == -1 || info->player == SDL_GetGamepadInstancePlayerIndex(event->cbutton.which)))
				info->callback(info->additionalData);
		
		return 0;
	};

	//Store additional information needed in the filter
	info.callback = callback;
	info.additionalData = additionalData;
	info.buttonBindings = &mButtonBindings;
	info.buttonName = name;
	info.player = mButtons[name].player;

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

Vector2<> me::InputManager::getMousePositon()
{
	SDL_GetMouseState(&mouseX, &mouseY);

	return Vector2<>(mouseX, mouseY);
}

int InputManager::watchControllers(void* userdata, SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_EVENT_GAMEPAD_ADDED:
	{
		SDL_Gamepad* gamepad = SDL_OpenGamepad(event->cdevice.which);

#ifdef _DEBUG
		std::cout << SDL_GetGamepadName(gamepad) << " detected.	Player: " 
			<< SDL_GetGamepadPlayerIndex(gamepad) << "	ID: " << event->cdevice.which << "\n";
#endif
	}
		break;
	case SDL_EVENT_GAMEPAD_REMOVED:
	{
		SDL_Gamepad* gamepad = SDL_GetGamepadFromInstanceID(event->cdevice.which);

#ifdef _DEBUG
			std::cout << SDL_GetGamepadName(gamepad) << " removed. ID: " << event->cdevice.which << "\n";
#endif

		SDL_CloseGamepad(gamepad);
	}
		break;
	default:
		break;
	}
		
	return 0;
}

int InputManager::updateInputData(void* userdata, SDL_Event* event)
{
	Input input = getInput(event);

	//Update all buttons binded to that input
	auto bindings = instance()->mButtonBindings.equal_range(input);
	for (auto binding = bindings.first; binding != bindings.second; binding++)
		instance()->mButtons[binding->second].pressed = EVENT_BUTTON_DOWN;

	//Return all unactive axis towards zero
	for (auto& axis : instance()->mAxis)
		if (axis.second.active)
			continue;
		else if (axis.second.value > 0)
			axis.second.value = std::max(.0f, axis.second.value - axis.second.gravity);
		else 
			axis.second.value = std::min(.0f, axis.second.value + axis.second.gravity);

	//Update all axis binded to that input
	if (input.type == INPUTTYPE_GAMEPAD_AXIS) {
		bindings = instance()->mPositiveAxisBindings.equal_range(input);
		for (auto binding = bindings.first; binding != bindings.second; binding++) {
			Axis* axis = &instance()->mAxis[binding->second];
			axis->value = input.value;
			axis->active = std::abs(input.value) > axis->dead;
		}
	}
	else {
		bindings = instance()->mPositiveAxisBindings.equal_range(input);
		for (auto binding = bindings.first; binding != bindings.second; binding++) {
			instance()->mAxis[binding->second].active = EVENT_BUTTON_DOWN;
			instance()->mAxis[binding->second].value = 1;
		}
		bindings = instance()->mNegativeAxisBindings.equal_range(input);
		for (auto binding = bindings.first; binding != bindings.second; binding++) {
			instance()->mAxis[binding->second].active = EVENT_BUTTON_DOWN;
			instance()->mAxis[binding->second].value = -1;
		}
	}

	return 0;
}

Input me::InputManager::getInput(SDL_Event* event)
{
	Input input;
	switch (event->type)
	{
	case SDL_EVENT_KEY_DOWN:
		//Don't repeat button down events
		if (event->key.repeat) {
			input.type = INPUTTYPE_NULL;
			input.which = -1;
			break;
		}
	case SDL_EVENT_KEY_UP:
		input.type = INPUTTYPE_KEYBOARD;
		input.which = event->key.keysym.sym;
		break;
	case SDL_EVENT_MOUSE_BUTTON_UP:
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		input.type = INPUTTYPE_MOUSE_CLICK;
		input.which = event->button.button;
		break;
	case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
	case SDL_EVENT_GAMEPAD_BUTTON_UP:
		input.type = INPUTTYPE_GAMEPAD_BUTTON;
		input.which = event->cbutton.button;
		break;
	case SDL_EVENT_GAMEPAD_AXIS_MOTION:
		input.type = INPUTTYPE_GAMEPAD_AXIS;
		input.which = event->caxis.axis;
		input.value = std::max(-1.0f, (float) event->caxis.value / SHRT_MAX);
		break;
	case SDL_EVENT_MOUSE_WHEEL:
		input.type = INPUTTYPE_MOUSE_WHEEL;
		input.which = event->wheel.direction;
		break;
	case SDL_EVENT_MOUSE_MOTION:

	default:
		input.type = INPUTTYPE_NULL;
		input.which = -1;
		break;
	}

	return input;
}
