#pragma once
#ifndef __SDL_WINDOW
#define __SDL_WINDOW

#include "Utils/Singleton.h"
#include <SDL3/SDL_init.h>

class SDL_Window;

namespace me {
	class Window : public Singleton<Window>
	{
		friend Singleton<Window>;

		Window(Uint32 flags = SDL_INIT_EVERYTHING);

		SDL_Window* window;

	public:
		~Window();
		
		SDL_Window* create(const char* name, int x, int y, int w, int h, Uint32 flags);

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

