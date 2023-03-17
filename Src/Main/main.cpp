/*
* This file contains the function "main". The execution of the program starts here and ends here
*/

#include "MotorEngine/MotorEngine.h"

#ifdef _DEBUG
#include "Utils/checkML.h"

using namespace me;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#else
#include <Windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
#endif

    /*
    * Create and initialize the engine
    * All libraries and components that the engine is going to use (Render, Physics, UI...)
    * In case of the setup of the engine fails, the game can't start and the program returns an error value (-1)
    */
    if (motorEngine().setup()) {
        /*
        * The main loop of the game
        * It is responsible of calculating the time between frames and when the game
        * does one iteration (Render, Physics, SceneManager, Audio, UI)
        */
        motorEngine().loop();

        /*
        * Delete all the memory created
        */
        motorEngine().exit();
    }
    else
        return -1;

    return 0;
}

