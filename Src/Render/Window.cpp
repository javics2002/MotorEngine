#include "Window.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

using namespace me;

Window::Window()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Motor Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_SOFTWARE);
}

Window::Window(uint32_t sdlFlags, const char* name, int x, int y, int w, int h, uint32_t windowFlags)
{
	mWidth = w;
	mHeight = h;
	SDL_Init(sdlFlags);
	window = SDL_CreateWindow(name, x, y, w, h, windowFlags);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_SOFTWARE);
}

Window::~Window()
{
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_Quit();
	}
}

SDL_Window* Window::get()
{
	return window;
}

int Window::getWindowWidth()
{
	SDL_GetWindowSize(window, &mWidth, &mHeight);
	return mWidth;
}

int Window::getWindowHeight()
{
	SDL_GetWindowSize(window, &mWidth, &mHeight);
	return mHeight;
}
