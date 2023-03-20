#pragma once
#ifndef __RENDER_WINDOW
#define __RENDER_WINDOW

#include "Utils/Singleton.h"

typedef struct SDL_Window SDL_Window;

namespace me {
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
	class Window : public Singleton<Window>
	{
		friend Singleton<Window>;

		/**
		Initializes SDL and creates an 854x480 SDL window named "Motor Engine",
		and will take input focus
		*/
		Window();

		/**
		Intitialices SDL and creates an SDL Window.
		@param sdlFlags 0, or one or more SDL_InitFlags OR'd together
		@param name name of the window in UTF-8 encoding.
		@param x, y position of the window. Use `SDL_WINDOWPOS_CENTERED` or `SDL_WINDOWPOS_UNDEFINED`.
		@param w, h width and height of the window in screen coordinates
		@param windowFlags 0, or one or more SDL_WindowFlags OR'd together
		@returns The window that was created or NULL on failure. Call SDL_GetError() for more information.
		*/
		Window(uint32_t sdlFlags, const char* name, int x, int y, int w, int h, uint32_t windowFlags);

		//Reference to SDL Window class
		SDL_Window* window;

	public:
		~Window();

		/**
		* @returns The window that was created or NULL on failure. Call SDL_GetError() for more information.
		*/
		SDL_Window* get();
	};

	/**
	This macro defines a compact way for using the singleton Window, instead of
	writing Window::instance()->method() we write win().method()
	*/
	inline Window& window() {
		return *Window::instance();
	};
}

#endif

