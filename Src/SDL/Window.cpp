#include "Window.h"
#include <SDL3/SDL_video.h>

using namespace me;

Window::Window(Uint32 flags)
{
	SDL_Init(flags);
}

Window::~Window()
{
}

SDL_Window* Window::create(const char* name, int x, int y, int w, int h, Uint32 flags)
{
	return window = SDL_CreateWindow(name, x, y, w, h, flags);
}

SDL_Window* me::Window::get()
{
	return window;
}
