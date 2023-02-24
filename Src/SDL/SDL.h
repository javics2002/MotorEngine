#pragma once

namespace me {
	/**
	InputManager provides information and callbacks for any user input.
	You can access input by key, but you can also define your own
	buttons to easely remap your game's controls.
	You can access the InputManager just calling im().
	*/
	class InputManager;

	/**
	Manages a SDL_Window instance so it can be shared among several modules like Ogre and Bullet.
	By default, it'll initialize SDL and create an 854x480 SDL window named "Motor Engine",
	and will take input focus.
	Initialize the window with:
	Window::init(Uint32 sdlFlags, const char* name, int x, int y, int w, int h, Uint32 windowFlags);
	and access the window with win().get();
	@param sdlFlags 0, or one or more SDL_InitFlags OR'd together
	@param name name of the window in UTF-8 encoding.
	@param x, y position of the window. Use `SDL_WINDOWPOS_CENTERED` or `SDL_WINDOWPOS_UNDEFINED`.
	@param w, h width and height of the window in screen coordinates
	@param windowFlags 0, or one or more SDL_WindowFlags OR'd together
	*/
	class Window;

	/**
	Representation of a virtual button, so you can unify input
	given any controller, keyboard or mouse.
	*/
	struct Button;

	/**
	Representation of a virtual axis, so you can unify input
	given any controller, keyboard or mouse
	*/
	struct Axis;

	//This data defines the behaviour of the axis
	struct AxisInfo;

	//Represents a physical button or key that can trigger a virtual button
	struct Input;

	//Represents two physical buttons or keys that can trigger a virtual axis
	struct AxisInput;
}