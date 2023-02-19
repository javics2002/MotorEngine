#pragma once
#ifndef __SDL_BUTTON
#define __SDL_BUTTON

#include <string>

namespace me {
	/**
	Representation of a virtual button, so you can unify input
	given any controller, keyboard or mouse
	*/
	struct Button {
		char id;
		std::string name;
		bool pressed;
	};
}

#endif