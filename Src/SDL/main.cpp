#ifdef _DEBUG
#pragma once
#ifndef __SDL_MAIN
#define __SDL_MAIN

#include "InputManager.h"
#include "Window.h"
#include <iostream>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_gamepad.h>

#define KEY_NAME SDL_GetKeyName(event->key.keysym.sym)

using namespace me;

int revealKeyboardEvents(void* userdata, SDL_Event* event)
{
    char* name = (char*) userdata; 

    if (event->type == SDL_EVENT_KEY_DOWN && !event->key.repeat)
        std::cout << name << " ha pulsado la tecla " << KEY_NAME << "\n";
    else if (event->type == SDL_EVENT_KEY_UP)
        std::cout << name << " ha soltado la tecla " << KEY_NAME << "\n";
    else if (event->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN)
        std::cout << name << " ha pulsado el boton del mando " << event->cbutton.button << "\n";

    return 0;
}

int interact(void* userdata)
{
    std::cout << "Interacting!\n";

    return 0;
}

int toggleInteract(void* userdata)
{
    bool* interactActive = (bool*) userdata;
    if (*interactActive)
        im().deleteOnButtonPressedEvent("Interact", interact, NULL);
    else
        im().addOnButtonPressedEvent("Interact", interact, NULL);

    *interactActive = !*interactActive;

    return 0;
}

int shoot(void* userdata)
{
    std::cout << "Shooting!\n";

    return 0;
}

int main() {
	im();
    Window::init(SDL_INIT_EVERYTHING, "Input Manager Test", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 854, 480, SDL_WINDOW_INPUT_FOCUS);

    //char* name = (char*) "Javi";
    //SDL_AddEventWatch(revealKeyboardEvents, name);
    ////Se copia name, asi que creo que no se le pueden pasar datos que puedan cambiar
    ////Si cambio name despues sigue diciendo Javi
    //name = (char*) "Rayo";

    Input keyboardE;
    keyboardE.type = SDL_EVENT_KEY_DOWN;
    keyboardE.which = SDLK_e;

    im().addButton("Interact", keyboardE);

    bool interactActive = false;

    Input keyboardSpace;
    keyboardSpace.type = SDL_EVENT_KEY_DOWN;
    keyboardSpace.which = SDLK_SPACE;
    im().addButton("Space", keyboardSpace);

    im().addOnButtonPressedEvent("Space", toggleInteract, &interactActive);

    Input leftClick;
    leftClick.type = SDL_EVENT_MOUSE_BUTTON_DOWN;
    leftClick.which = SDL_BUTTON_LEFT;
    im().addButton("Shoot", leftClick);

    im().addOnButtonPressedEvent("Shoot", shoot);

    Input controllerA;
    controllerA.type = SDL_EVENT_GAMEPAD_BUTTON_DOWN;
    controllerA.which = SDL_GAMEPAD_BUTTON_A;

    im().addButton("A", controllerA);

    im().addOnButtonPressedEvent("A", shoot);

    std::cout << "Use Space to toogle Interact. Use E to interact when Interact is enabled.\n";

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            return 0;
        }
    }
    std::cout << SDL_GetError();
	return 0;
}

#endif
#endif