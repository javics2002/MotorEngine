// Motor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>

#include "Ogre/Ogre.h"

using namespace std;

int main()
{
    initOgre("Juego");
    cout << "MotorEngine listo!\n";
    int a;
    std::cin >> a;
    return 0;
}

