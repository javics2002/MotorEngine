#pragma once
#ifndef __MOTORENGINE_MOTORENGINEERROR
#define __MOTORENGINE_MOTORENGINEERROR

#include "MotorEngineAPI.h"
#include <string>

namespace me {
	extern "C" {
		/**
		Throws a Windows error window with custom title and message.
		@params title Title of the window
		@params message Message of the window
		*/
		__MOTORENGINE_API void throwMotorEngineError(std::string title, std::string message);
	}
}
#endif