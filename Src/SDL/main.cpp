#ifdef _DEBUG
#pragma once
#ifndef __SDL_MAIN
#define __SDL_MAIN

#include "Utils/Utils.h"
#include "InputManager.h"
#include <iostream>

int main() {
	me::im().saluda();
	me::im().init();
	return 0;
}

#endif
#endif