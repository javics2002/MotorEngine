#ifdef _DEBUG
#pragma once
#ifndef __GUI_MAIN
#define __GUI_MAIN

#include <iostream>

#include "Render/OgreManager.h"
#include "Render/Window.h"
#include "GUI/GUIManager.h"

using namespace me;

int main() {

    win();
    om().render();

    GUIManager::init();
    guim().loadScheme("TaharezLook.scheme");
    guim().setFont("DejaVuSans-10");
    guim().createWidget("TaharezLook/Button", Vector4(0.5f, 0.5f, 0.1f, 0.05f), Vector4(), "TestButton");

    guim().draw();

    return 0;
}

#endif
#endif