#pragma once
#ifndef __SDL_INPUT_MANAGER
#define __SDL_INPUT_MANAGER

#include "Button.h"
#include "Utils/Singleton.h"
#include <vector>
#include <map>

union SDL_Event;
typedef int (*SDL_EventFilter)(void* userdata, SDL_Event* event);

namespace me {
	/**
	InputManager provides information and callbacks for any user input.
	You can access input by key, but you can also define your own
	buttons to easely remap your game's controls.
	You can access the InputManager just calling im().
	*/
	class InputManager : public Singleton<InputManager> {
		friend Singleton<InputManager>;

		InputManager();

		//Initial size of mButtons vector
		const char M_INITIAL_BUTTONS = 16;

		//Number of buttons currently existing
		char mButtonsSize;

		//Managed buttons
		std::vector<Button> mButtons;

		//Pairs each button with its name
		std::map<std::string, Button*> mButtonNames;

	public:
		InputManager& operator=(const InputManager& o) = delete;
		InputManager(const InputManager& o) = delete;
		~InputManager() override;

		//To be implemented
		bool addEvent(SDL_EventFilter* filter, void* userdata);
		bool deleteEvent(SDL_EventFilter* filter, void* userdata);
		bool addButton(char* name);
		bool deleteButton(char* name);
		bool addOnButtonPressedEvent(char* buttonName, SDL_EventFilter* filter, void* userdata);
		bool deleteOnButtonPressedEvent(char* buttonName, SDL_EventFilter* filter, void* userdata);
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