#pragma once
#ifndef __MOTORENGINE_MOTORENGINEERROR
#define __MOTORENGINE_MOTORENGINEERROR

#include <string>

namespace me {
	/**
	Throws a Windows error window with custom title and message.
	@params title Title of the window
	@params message Message of the window
	*/
	void throwMotorEngineError(std::string title, std::string message);
}
#endif