#pragma once
#ifndef __INPUT_AXIS
#define __INPUT_AXIS

#include <string>

namespace me {
	enum InputType : int;

	//This data defines the behaviour of the axis
	struct __MOTORENGINE_API AxisInfo {
		//Speed in units per second that the axis falls toward neutral when no input is present.
		float gravity;

		/*How far the user needs to move an analog stick before your application registers the movement.
		At runtime, input from all analog devices that falls within this range will be considered null.*/
		float dead;
	};

	/**
	Representation of a virtual axis, so you can unify input
	given any controller, keyboard or mouse
	*/
	struct __MOTORENGINE_API Axis : AxisInfo {
		//Normalized value
		float value;

		//Whether the axis is receiving input
		bool active;
	};

	//Represents two physical buttons or keys that can trigger a virtual axis
	struct __MOTORENGINE_API AxisInput {
		/*
		INPUTTYPE_KEYBOARD for keyboard key presses
		INPUTTYPE_MOUSE for mouse clicks
		INPUTTYPE_GAMEPAD for controller presses
		INPUTTYPE_NULL for invalid input
		*/
		InputType type;

		/*Which key, mouse button, or controller button has been pressed.
		Represents a value of SDL_KeyCode, SDL_BUTTON or SDL_GamepadButton depending on the type of the event*/
		union {
			/*In case it is a physical axis, which will be used instead of two buttons.*/
			int which;

			int positive;
		};
		int negative;
	};
}

#endif