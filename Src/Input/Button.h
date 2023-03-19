#pragma once
#ifndef __INPUT_BUTTON
#define __INPUT_BUTTON

#include <string>
#include <unordered_map>
#include <SDL3/SDL_events.h>

namespace me {
	enum InputType : int;

	/**
	Representation of a virtual button, so you can unify input
	given any controller, keyboard or mouse.
	*/
	struct Button {
		//Value
		bool pressed;

		/*Whose player this button is, used in case its a gamepad button press
		-1 will be considered as a playerless input.*/
		int player;
	};

	//Represents a physical button or key that can trigger a virtual button.
	struct Input {
		/*
		INPUTTYPE_KEYBOARD for keyboard key presses
		INPUTTYPE_MOUSE for mouse clicks
		INPUTTYPE_GAMEPAD for controller presses
		INPUTTYPE_NULL for invalid input
		*/
		InputType type;
		
		/*Which key, mouse button, or controller button has been pressed.
		Represents a value of SDL_KeyCode, SDL_BUTTON or SDL_GamepadButton depending on the type of the event.*/
		int which;

		/*In case it is a gamepad axis motion, or a mouse motion, the value will be stored here*/
		float value;
		

		bool operator==(const Input& i) const
		{
			return type == i.type && which == i.which;
		}
	};

	//Provides hash suppport for using struct Input as a key in std::unordered_map
	struct InputHasher {
		size_t operator()(const Input& t) const {
			return std::hash<int>()(t.which) ^ std::hash<int>()(t.type);
		}
	};

	/*
	Stores data for virtual buttons' callbacks.
	*/
	struct OnButtonPressedInfo {
		//Simple callback provided by the user.
		int(*callback)(void*); 

		//Additional userdata given to callback as a parameter.
		void* additionalData;

		//Filtered callback that calls callback if the event source matches any of the virtual button's bindings.
		SDL_EventFilter filter;

		//Reference to InputManager's mButtonBindings multimap.
		std::unordered_multimap<Input, std::string, InputHasher>* buttonBindings; 

		//Name of the button this callback belongs to.
		std::string buttonName;

		/*Whose player this button is, used in case its a gamepad button press.
		The first player is 0.
		-1 will be considered as a playerless input.*/
		int player;
	};
}

#endif