#pragma once
#ifndef __MOTORENGINE_MOTORENGINEERROR
#define __MOTORENGINE_MOTORENGINEERROR

#include "MotorEngineAPI.h"
#include "Utils/Singleton.h"
#include <string>

namespace me {
	/**
	* This class provides functionality to create a Windows Error box
	* to notify blocking and unrecoverable errors.
	*/
	class __MOTORENGINE_API ErrorManager : public Singleton<ErrorManager> {
		friend Singleton<ErrorManager>;

		ErrorManager();

	public:
		~ErrorManager();

		/**
		Throws a Windows error window with custom title and message.
		@params title Title of the window
		@params message Message of the window
		*/
		void throwMotorEngineError(std::string title, std::string message);
	};

	/**
	This macro defines a compact way for using the singleton ErrorManager,
	instead of writing ErrorManager::instance()->method() we write errorManager().method()
	*/
	inline ErrorManager& errorManager() {
		return *ErrorManager::Instance();
	};
}
#endif