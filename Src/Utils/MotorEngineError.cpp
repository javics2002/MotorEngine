#include "MotorEngineError.h"
#include <Windows.h>

void me::throwMotorEngineError(std::string title, std::string message)
{
	std::wstring wTitle = std::wstring(title.begin(), title.end());
	std::wstring wMessage = std::wstring(message.begin(), message.end());

	MessageBox(NULL, wMessage.c_str(), wTitle.c_str(), MB_ICONERROR | MB_OK);
}
