#pragma once
#ifndef __SDL_AXIS
#define __SDL_AXIS

#include <string>
#include <SDL3/SDL_events.h>

namespace me {
	//This data defines the behaviour of the axis
	struct AxisInfo {
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
	struct Axis : AxisInfo {
		//Normalized value
		float value;
	};

	//Represents two physical buttons or keys that can trigger a virtual axis
	struct AxisInput {
		/*
		SDL_KeyboardEvent for keyboard key presses
		SDL_MouseButtonEvent for mouse clicks
		SDL_ControllerButtonEvent for controller presses
		*/
		SDL_EventType type;

		/*Which key, mouse button, or controller button has been pressed.
		Represents a value of SDL_KeyCode, SDL_BUTTON or SDL_GamepadButton depending on the type of the event*/
		int positive, negative;
	};
}

#endif