#include "Window.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>

using namespace me;

Window::Window()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Motor Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
}

Window::Window(uint32_t sdlFlags, const char* name, int x, int y, int w, int h, uint32_t windowFlags)
{
	SDL_Init(sdlFlags);
	window = SDL_CreateWindow(name, x, y, w, h, windowFlags);
}

Window::~Window()
{
}

SDL_Window* me::Window::get()
{
	return window;
}
