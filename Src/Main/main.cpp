// Motor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>

#include "Main/MotorEngine.h"

using namespace std;

int main()
{
    me::MotorEngine engine;
    engine.setup();

    cout << "MotorEngine listo!\n";
    int a;
    std::cin >> a;
    return 0;
}

