#ifdef _DEBUG
#pragma once
#ifndef __INPUT_MAIN
#define __INPUT_MAIN

#include "InputManager.h"
#include "Render/Window.h"
#include "Utils/checkML.h"
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

int getAxisValue(void* userdata) {
    char* name = (char*) userdata;
    std::cout << name << " axis value: " << im().getAxis(name) << "\n";

    return 0;
}

int getMousePosition(void* userdata) {
    std::cout << "Mouse pos: " << im().getMousePositon().x << " " << im().getMousePositon().y << "\n";

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
    keyboardE.type = INPUTTYPE_KEYBOARD;
    keyboardE.which = SDLK_e;

    im().addButton("Interact", keyboardE);

    bool interactActive = false;

    Input keyboardSpace;
    keyboardSpace.type = INPUTTYPE_KEYBOARD;
    keyboardSpace.which = SDLK_SPACE;
    im().addButton("Space", keyboardSpace);

    im().addOnButtonPressedEvent("Space", toggleInteract, &interactActive);

    Input leftClick;
    leftClick.type = INPUTTYPE_MOUSE_CLICK;
    leftClick.which = SDL_BUTTON_LEFT;
    im().addButton("Shoot", leftClick);

    im().addOnButtonPressedEvent("Shoot", shoot);

    Input controllerA;
    controllerA.type = INPUTTYPE_GAMEPAD_BUTTON;
    controllerA.which = SDL_GAMEPAD_BUTTON_A;

    im().addButton("A", controllerA, 0); //Solo P1

    im().addOnButtonPressedEvent("A", shoot);

    AxisInput horizontal;
    horizontal.type = INPUTTYPE_KEYBOARD;
    horizontal.positive = SDLK_d;
    horizontal.negative = SDLK_a;

    AxisInfo horizontalInfo;
    horizontalInfo.dead = .1f;
    horizontalInfo.gravity = .01f;

    char* horizontalName = (char*) "Horizontal";
    im().addAxis(horizontalName, horizontalInfo, horizontal);

    AxisInput gamepadLeftHorizontal;
    gamepadLeftHorizontal.type = INPUTTYPE_GAMEPAD_AXIS;
    gamepadLeftHorizontal.which = SDL_GAMEPAD_AXIS_LEFTX;

    im().addBinding("Horizontal", gamepadLeftHorizontal);

    Input keyboardP;
    keyboardP.type = INPUTTYPE_KEYBOARD;
    keyboardP.which = SDLK_p;

    im().addButton("P", keyboardP);
    im().addOnButtonPressedEvent("P", getAxisValue, horizontalName);

    Input keyboardM;
    keyboardM.type = INPUTTYPE_KEYBOARD;
    keyboardM.which = SDLK_m;

    im().addButton("M", keyboardM);
    im().addOnButtonPressedEvent("M", getMousePosition);


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