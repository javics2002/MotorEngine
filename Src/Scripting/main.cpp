#ifdef _DEBUG
#pragma once
#ifndef __LUA_MAIN
#define __LUA_MAIN

// main.cpp : Define las funciones de la biblioteca estática.
//

#include "pch.h"
#include "framework.h"

#include <iostream>
#include <string>

void sayHello(const std::string& name) {
    std::cout << "Hola, " << name << "!" << std::endl;
};

std::string takeName() {
    std::string name;
    std::cout << "Ingresa tu nombre: ";
    std::getline(std::cin, name);
    return name;
};

int ejemplo1() { // Carga de funciones
    lua_State* L = luaL_newstate(); // crea un nuevo estado de Lua
    luaL_openlibs(L); // abre las bibliotecas estándar de Lua

    luabridge::getGlobalNamespace(L)
        .addFunction("printMessage", sayHello);

    // Debería de poder funcionar también con funciones lambda del tipo:
    //.addFunction("printMessage", []() { std::cout << "Hola, mundo" << std::endl; });

    luaL_dostring(L, ("printMessage('" + takeName() + "')").c_str()); // ejecuta el script de Lua

    // Sin argumentos:
    //luaL_dostring(L, "printMessage()"); // ejecuta el script de Lua

    lua_close(L); // libera el estado de Lua

    return 0;
};

int ejemplo2() { // Carga de datos
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Cargar el archivo de datos Lua
    luaL_dofile(L, "datos.lua");

    // Leer los datos del archivo Lua
    std::string nombre = luabridge::getGlobal(L, "nombre");
    std::string apellido = luabridge::getGlobal(L, "apellido");
    int edad = luabridge::getGlobal(L, "edad");

    // Transcribir los datos leídos
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Apellido: " << apellido << std::endl;
    std::cout << "Edad: " << edad << std::endl;

    lua_close(L);
    return 0;
};

// TODO: Ejemplo de una función de biblioteca
int main()
{
    std::string selection;
    std::cout << "Elige un ejemplo [A/B]: ";
    std::getline(std::cin, selection);
    
    if (selection.at(0) == 'A' || selection.at(0) == 'a') {
        return ejemplo1();
    }
    else if (selection.at(0) == 'B' || selection.at(0) == 'b') {
        return ejemplo2();
    };

    return -1;
};

#endif
#endif