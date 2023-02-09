// Motor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include "Biblioteca.h"

#include <OgreRoot.h>

using namespace std;

int main()
{
    //fstream f("Assets\\Mapa.txt");

    //if (f.is_open()) {
    //    cout << "FICHERO ABIERTO\n";
    //    f.close();
    //}

    //else {
    //    cerr << "FICHERO NO ENCONTRADO\n";
    //    return 1;
    //}

    Ogre::Root* root;
    root = new Ogre::Root();

    saluda("Diego");

    return 0;
}

