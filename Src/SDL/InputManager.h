#pragma once
#ifndef __SDL_INPUT_MANAGER
#define __SDL_INPUT_MANAGER

#include "Utils/Singleton.h"
#include "Button.h"
#include "Axis.h"
#include <vector>
#include <string>
#include <unordered_map>

namespace me {
	enum InputType { INPUTTYPE_KEYBOARD, INPUTTYPE_MOUSE, INPUTTYPE_GAMEPAD, INPUTTYPE_NULL };

	/**
	InputManager provides information and callbacks for any user input from
	keyboard, mouse and game controller.
	Define virtual buttons to easely remap your game's controls.
	You can access the InputManager just calling im().
	*/
	class InputManager : public Singleton<InputManager> {
		friend Singleton<InputManager>;

		InputManager();

		std::unordered_map<std::string, Button> mButtons;		//Pairs each button with its name.
		std::unordered_map<std::string, Axis> mAxis;			//Pairs each axis with its name.

		//Stores virtual button names linked to their physical input.
		std::unordered_multimap<Input, std::string, InputHasher> mButtonBindings;
		//Stores virtual axis names linked to their physical positive input.
		std::unordered_multimap<Input, std::string, InputHasher> mPositiveAxisBindings;
		//Stores virtual axis names linked to their physical negative input.
		std::unordered_multimap<Input, std::string, InputHasher> mNegativeAxisBindings;

		//Stores callback data for virtual buttons.
		std::unordered_multimap<std::string, OnButtonPressedInfo> mOnButtonPressed;

		//Stores each player's gamepad
		std::unordered_map<int, SDL_Gamepad*> mGamepads;

		/*
		Manages the connection and disconnection of controllers.
		*/
		static int watchControllers(void* userdata, SDL_Event* event);

		/*
		Updates button and axis' data
		*/
		static int updateInputData(void* userdata, SDL_Event* event);

		/*
		Constructs input struct for any given event
		*/
		static Input getInput(SDL_Event* event);

	public:
		InputManager& operator=(const InputManager& o) = delete;
		InputManager(const InputManager& o) = delete;
		~InputManager() override;
		
		/**
		Calls filter everytime an SDL_Event is processed.
		@param filter is a function with the format:
		int (*SDL_EventFilter)(void* userdata, SDL_Event* event).
		It is recommended to check the type of the event in it.
		@param userdata is a pointer to additional information to use in the callback.
		It is NULL by default.
		*/
		void addEvent(SDL_EventFilter filter, void* userdata = NULL);
		/**
		Deletes filter from the SDLEventWatch.
		@param filter is the same function used to add the callback.
		@param userdata is the same additional information used when adding the callback.
		*/
		void deleteEvent(SDL_EventFilter filter, void* userdata = NULL);

		/**
		Creates a button of name name.
		@param name Name of the button.
		@returns A boolean representing whether the button could be created.
		*/
		bool addButton(std::string name);
		/**
		Creates a button of name name and binds it with some physical input.
		@param name Name of the button.
		@param input Representation of the physical input.
		input.type can be SDL_KeyboardEvent for keyboard key presses,
		SDL_MouseButtonEvent for mouse clicks,
		or SDL_ControllerButtonEvent for controller presses;
		and input.which represents a value of SDL_KeyCode, SDL_BUTTON 
		or SDL_GamepadButton depending on the type of the event
		@returns A boolean representing whether the button could be created.
		*/
		bool addButton(std::string name, Input input);
		/**
		Deletes button name and any bindings it may have.
		@param name Name of the button.
		@returns A boolean representing whether the button was deleted.
		*/
		bool deleteButton(std::string name);

		/**
		Creates an axis of name name.
		@param name Name of the axis.
		@param info Defines the behaviour of the axis.
		info.gravity is the speed in units per second 
		that the axis falls toward neutral when no input is present
		and info.dead is how far the user needs to move an analog stick 
		before your application registers the movement.
		@returns A boolean representing whether the button could be created.
		*/
		bool addAxis(std::string name, AxisInfo info);
		/**
		Creates an axis of name name and binds it with some physical input.
		@param name Name of the axis.
		@param info Defines the behaviour of the axis.
		info.gravity is the speed in units per second
		that the axis falls toward neutral when no input is present
		and info.dead is how far the user needs to move an analog stick
		before your application registers the movement.
		@param input Represents two physical buttons or keys that can trigger a virtual axis.
		input.type can be SDL_KeyboardEvent for keyboard key presses,
		SDL_MouseButtonEvent for mouse clicks,
		or SDL_ControllerButtonEvent for controller presses;
		and input.positive and input.negative represents a value of SDL_KeyCode, SDL_BUTTON
		or SDL_GamepadButton depending on the type of the event
		@returns A boolean representing whether the button could be created.
		*/
		bool addAxis(std::string name, AxisInfo info, AxisInput input);
		/**
		Deletes axis name and any bindings it may have.
		@param name Name of the axis.
		@returns A boolean representing whether the axis was deleted.
		*/
		bool deleteAxis(std::string name);

		/**
		Binds some physical input with a virutal button,
		so triggering said input will trigger the virtual button.
		@param name Name of the button.
		@param input Representation of the physical input.
		input.type can be SDL_KeyboardEvent for keyboard key presses,
		SDL_MouseButtonEvent for mouse clicks,
		or SDL_ControllerButtonEvent for controller presses;
		and input.which represents a value of SDL_KeyCode, SDL_BUTTON
		or SDL_GamepadButton depending on the type of the event
		@returns A boolean representing whether the binding was successful.
		*/
		bool addBinding(std::string name, Input input);
		/**
		Binds some physical input with a virutal axis,
		so triggering said input will trigger the virtual axis.
		@param name Name of the axis.
		@param input Represents two physical buttons or keys that can trigger a virtual axis.
		input.type can be SDL_KeyboardEvent for keyboard key presses,
		SDL_MouseButtonEvent for mouse clicks,
		or SDL_ControllerButtonEvent for controller presses;
		and input.positive and input.negative represents a value of SDL_KeyCode, SDL_BUTTON
		or SDL_GamepadButton depending on the type of the event
		@returns A boolean representing whether the binding was successful.
		*/
		bool addBinding(std::string name, AxisInput input);
		/**
		Unlinks a button with some physical input
		@param name Name of the button.
		@param input Representation of the physical input.
		input.type can be SDL_KeyboardEvent for keyboard key presses,
		SDL_MouseButtonEvent for mouse clicks,
		or SDL_ControllerButtonEvent for controller presses;
		and input.which represents a value of SDL_KeyCode, SDL_BUTTON
		or SDL_GamepadButton depending on the type of the event
		@returns A boolean representing whether the binding was deleted.
		*/
		bool deleteBinding(std::string name, Input input);
		/**
		Unlinks an axis with some physical input
		@param name Name of the axis.
		@param input Represents two physical buttons or keys that can trigger a virtual axis.
		input.type can be SDL_KeyboardEvent for keyboard key presses,
		SDL_MouseButtonEvent for mouse clicks,
		or SDL_ControllerButtonEvent for controller presses;
		and input.positive and input.negative represents a value of SDL_KeyCode, SDL_BUTTON
		or SDL_GamepadButton depending on the type of the event
		@returns A boolean representing whether the binding was deleted.
		*/
		bool deleteBinding(std::string name, AxisInput input);
		
		/**
		@param name Name of the button.
		@returns The state of the button.
		*/
		bool getButton(std::string name);
		/**
		@param name Name of the axis.
		@returns The value of the axis in range [-1, 1].
		*/
		float getAxis(std::string name);

		/**
		Binds a callback to a virtual button, so it's executed anytime it's triggered.
		@param name Name of the button
		@param callback Callback to be binded to button name
		@param additionalData Parameter that the callback would be called with and it may use.
		@returns Whether the callback could be binded to the button
		*/
		bool addOnButtonPressedEvent(std::string name, int(*callback)(void*), void* additionalData = NULL);
		/**
		Unbinds a callback from its virtual button, so it's never executed again anytime its button is triggered.
		@param name Name of the button
		@param callback Callback to be unbinded to button name
		@param additionalData is the same additional information used when the callback was binded.
		@returns Whether the callback could be unbinded to the button
		*/
		bool deleteOnButtonPressedEvent(std::string name, int(*callback)(void*), void* additionalData = NULL);
	};

	/**
	This macro defines a compact way for using the singleton InputHandler, instead of
	writing InputHandler::instance()->method() we write ih().method()
	*/
	inline InputManager& im() {
		return *InputManager::instance();
	}
}

#endif