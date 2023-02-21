#pragma once
#ifndef __SDL_WINDOW
#define __SDL_WINDOW

#include "Utils/Singleton.h"
#include <SDL3/SDL_init.h>

class SDL_Window;

namespace me {
	/**
	Manages a SDL_Window instance so it can be shared among several modules like Ogre and Bullet.
	*/
	class Window : public Singleton<Window>
	{
		friend Singleton<Window>;

		Window(Uint32 flags = SDL_INIT_EVERYTHING);

		//Reference to SDL Window class
		SDL_Window* window;

	public:
		~Window();
		
		/**
		Creates and returns an SDL Window.
		@param name name of the window in UTF-8 encoding.
		@param x, y position of the window. Use `SDL_WINDOWPOS_CENTERED` or `SDL_WINDOWPOS_UNDEFINED`.
		@param w, h width and height of the window in screen coordinates
		@param flags 0, or one or more SDL_WindowFlags OR'd together
		@returns The window that was created or NULL on failure. Call SDL_GetError() for more information.
		*/
		SDL_Window* create(const char* name, int x, int y, int w, int h, Uint32 flags);

		/**
		* @returns Reference to the SDL_Window class managed by the singleton
		*/
		SDL_Window* get();
	};

	/**
	This macro defines a compact way for using the singleton Window, instead of
	writing Window::instance()->method() we write win().method()
	*/
	inline Window& win() {
		return *Window::instance();
	};
}

#endif

