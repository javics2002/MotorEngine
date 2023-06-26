#include "InputManager.h"

#include "InputCode.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_gamepad.h>
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
	SDL_AddEventWatch(WatchControllers, NULL);
	SDL_AddEventWatch(UpdateInputData, NULL);
	resetMotionControlValues();
}

InputManager::~InputManager()
{
}

void InputManager::addEvent(SDL_EventFilter filter, void* userdata)
{
	SDL_AddEventWatch(filter, userdata);
}

void InputManager::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {}
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
		auto bindings = info->buttonBindings->equal_range(GetInput(event));
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

Vector2 me::InputManager::getMousePositon()
{
	SDL_GetMouseState(&mMouseX, &mMouseY);
	return Vector2(mMouseX, mMouseY);
}

void me::InputManager::setMotionControlsSensitivity(float pitch, float yaw, float roll)
{
	mMotionControlsSensitivityPitch = pitch;
	mMotionControlsSensitivityYaw = yaw;
	mMotionControlsSensitivityRoll = roll;
}

void me::InputManager::resetMotionControlValues()
{
	mLastMotionControlPitchValue = 0.0f;
	mLastMotionControlYawValue = 0.0f;
	mLastMotionControlRollValue = 0.0f;
}

int InputManager::WatchControllers(void* userdata, SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_EVENT_GAMEPAD_ADDED:
	{
		SDL_Gamepad* gamepad = SDL_OpenGamepad(event->cdevice.which);

		Instance()->mControllers.insert(event->cdevice.which);
		if (SDL_GamepadHasSensor(gamepad, SDL_SENSOR_GYRO))
			SDL_SetGamepadSensorEnabled(gamepad, SDL_SENSOR_GYRO, SDL_bool(true));

#ifdef _DEBUG
		std::cout << SDL_GetGamepadName(gamepad) << " detected.	Player: " 
			<< SDL_GetGamepadPlayerIndex(gamepad) << "	ID: " << event->cdevice.which << "\n";
#endif
	}
		break;
	case SDL_EVENT_GAMEPAD_REMOVED:
		if (Instance()->mControllers.count(event->cdevice.which)) {
			SDL_Gamepad* gamepad = SDL_GetGamepadFromInstanceID(event->cdevice.which);

			Instance()->mControllers.erase(event->cdevice.which);
			if (SDL_GamepadHasSensor(gamepad, SDL_SENSOR_GYRO))
				SDL_SetGamepadSensorEnabled(gamepad, SDL_SENSOR_GYRO, SDL_bool(true));

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

int InputManager::UpdateInputData(void* userdata, SDL_Event* event)
{
	Input input = GetInput(event);

	//Update all buttons binded to that input
	auto bindings = Instance()->mButtonBindings.equal_range(input);
	for (auto binding = bindings.first; binding != bindings.second; binding++)
		//Check if its the right player
		if (input.type != INPUTTYPE_GAMEPAD_BUTTON || 
			(input.type == INPUTTYPE_GAMEPAD_BUTTON && (Instance()->mButtons[binding->second].player == -1 ||
			Instance()->mButtons[binding->second].player == SDL_GetGamepadInstancePlayerIndex(event->cbutton.which))))
			Instance()->mButtons[binding->second].pressed = EVENT_BUTTON_DOWN;

	//Return all unactive axis towards zero
	for (auto& axis : Instance()->mAxis)
		if (axis.second.active)
			continue;
		else if (axis.second.value > 0)
			axis.second.value = std::max(.0f, axis.second.value - axis.second.gravity);
		else 
			axis.second.value = std::min(.0f, axis.second.value + axis.second.gravity);

	//Update all axis binded to that input
	if (input.type == INPUTTYPE_GAMEPAD_AXIS) {
		bindings = Instance()->mPositiveAxisBindings.equal_range(input);
		for (auto binding = bindings.first; binding != bindings.second; binding++) 
			//Check if its the right player
			if (Instance()->mButtons[binding->second].player == -1 ||
				Instance()->mButtons[binding->second].player == SDL_GetGamepadInstancePlayerIndex(event->caxis.which)) {
				Axis* axis = &Instance()->mAxis[binding->second];
				axis->value = input.value;
				axis->active = std::abs(input.value) > axis->dead;
			}
	}
	else if (EVENT_BUTTON_DOWN) {
		bindings = Instance()->mPositiveAxisBindings.equal_range(input);
		for (auto binding = bindings.first; binding != bindings.second; binding++) {
			//Check if its the right player
			if (!(input.type != INPUTTYPE_GAMEPAD_BUTTON || 
				(input.type == INPUTTYPE_GAMEPAD_BUTTON && (Instance()->mButtons[binding->second].player == -1 ||
				Instance()->mButtons[binding->second].player == SDL_GetGamepadInstancePlayerIndex(event->cbutton.which)))))
				continue;

			if (Instance()->mAxis[binding->second].active && Instance()->mAxis[binding->second].value == -1)
				//The axis is being pressed in both positive and negative input
				Instance()->mAxis[binding->second].value = 0;
			else {
				Instance()->mAxis[binding->second].active = true;
				Instance()->mAxis[binding->second].value = 1;
			}
		}
		bindings = Instance()->mNegativeAxisBindings.equal_range(input);
		for (auto binding = bindings.first; binding != bindings.second; binding++) {
			//Check if its the right player
			if (!(input.type != INPUTTYPE_GAMEPAD_BUTTON ||
				(input.type == INPUTTYPE_GAMEPAD_BUTTON && (Instance()->mButtons[binding->second].player == -1 ||
				Instance()->mButtons[binding->second].player == SDL_GetGamepadInstancePlayerIndex(event->cbutton.which)))))
				continue;

			if (Instance()->mAxis[binding->second].active && Instance()->mAxis[binding->second].value == 1)
				//The axis is being pressed in both positive and negative input
				Instance()->mAxis[binding->second].value = 0;
			else {
				Instance()->mAxis[binding->second].active = true;
				Instance()->mAxis[binding->second].value = -1;
			}
		}
	}
	else if (EVENT_BUTTON_UP) {
		bindings = Instance()->mPositiveAxisBindings.equal_range(input);
		for (auto binding = bindings.first; binding != bindings.second; binding++) {
			if (Instance()->mAxis[binding->second].active && Instance()->mAxis[binding->second].value == 0)
				//The axis was already pressed in the negative input
				Instance()->mAxis[binding->second].value = -1;
			else
				Instance()->mAxis[binding->second].active = false;
		}
		bindings = Instance()->mNegativeAxisBindings.equal_range(input);
		for (auto binding = bindings.first; binding != bindings.second; binding++) {
			if (Instance()->mAxis[binding->second].active && Instance()->mAxis[binding->second].value == 0)
				//The axis was already pressed in the positive input
				Instance()->mAxis[binding->second].value = 1;
			else
				Instance()->mAxis[binding->second].active = false;
		}
	}

	return 0;
}

Input me::InputManager::GetInput(SDL_Event* event)
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
	case SDL_EVENT_GAMEPAD_SENSOR_UPDATE:
		if (event->csensor.sensor == SDL_SENSOR_GYRO) {
			input.type = INPUTTYPE_GAMEPAD_AXIS;
			input.which = GamepadAxisCode::GAMEPAD_AXISCODE_MOTION_ROLL;
			Instance()->mLastMotionControlRollValue += std::min(std::max(-1.0f, -event->csensor.data[2] * Instance()->mMotionControlsSensitivityRoll), 1.0f);
			input.value = Instance()->mLastMotionControlRollValue;
		}
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
