#ifdef _DEBUG
#pragma once
#ifndef __SDL_MAIN
#define __SDL_MAIN

#include "InputManager.h"
#include <iostream>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>

#define KEY_NAME SDL_GetKeyName(event->key.keysym.sym)

using namespace me;

int revealKeyboardEvents(void* userdata, SDL_Event* event)
{
    char* name = (char*) userdata;
    if (event->type == SDL_EVENT_KEY_DOWN && !event->key.repeat)
        std::cout << name << " ha pulsado la tecla " << KEY_NAME << "\n";
    else if (event->type == SDL_EVENT_KEY_UP)
        std::cout << name << " ha soltado la tecla " << KEY_NAME << "\n";
    return 0;
}

int main() {
	im();
    SDL_Init(SDL_INIT_EVERYTHING); //Poner solo los flags justos
    SDL_Window* window = SDL_CreateWindow("Input Manager Test", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WindowFlags::SDL_WINDOW_INPUT_FOCUS);

    char* name = (char*) "Javi";
    SDL_AddEventWatch(revealKeyboardEvents, name); 
    //Se copia name, asi que creo que no se le pueden pasar datos que puedan cambiar
    //Si cambio name despues sigue diciendo Javi
    name = (char*) "Rayo";

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            break;
        }
    }
    std::cout << SDL_GetError();
	return 0;
}

#endif
#endif