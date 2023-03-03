#ifdef _DEBUG
#pragma once
#ifndef __BULLET_MAIN
#define __BULLET_MAIN

#include <iostream>
#include <SDL3/SDL_events.h>

#include "PhysicsManager.h"
#include "SDL/Window.h"
#include "Utils/Vector3.h"

using namespace me;

int main() {
    
    pm();
    win();
    
    //pm().update(5);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            return 0;
        }
    }

    return 0;
}

#endif
#endif