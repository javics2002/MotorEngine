/*
* This file contains the function "main". The execution of the program starts here and ends here
*/

#include "MotorEngine.h"

using namespace std;

int main()
{
    me::MotorEngine engine;

    /*
    * Create and initialize the engine 
    * All libraries and components that the engine is going to use (Render, Physics, UI...)
    * In case of the setup of the engine fails, the game can't start and the program returns an error value (-1)
    */
    if (engine.setup() < 0)
        return -1;

    /*
    * The main loop of the game
    * It is responsible of calculating the time between frames and when the game
    * does one iteration (Render, Physics, SceneManager, Audio, UI)
    */
    engine.loop();

    /*
    * Delete all the memory created
    */
    engine.exit();

    return 0;
}

