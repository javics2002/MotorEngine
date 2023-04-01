#ifdef _DEBUG
#pragma once
#ifndef __GUI_MAIN
#define __GUI_MAIN

#include <iostream>

#include "Render/RenderManager.h"
#include "Render/Window.h"
#include "GUI/GUIManager.h"
#include "Render/RenderWindow.h"

#include <OgreRenderWindow.h>
#include <CEGUI/Window.h>

using namespace me;

int main() {
    
    window();
    renderManager().render();

    GUIManager::init();
    guiManager().loadScheme("TaharezLook.scheme");
    guiManager().setFont("DejaVuSans-10");
    CEGUI::Window* uiWin = guiManager().createWidget("TaharezLook/Button", Vector4(0.5f, 0.5f, 0.3f, 0.2f), Vector4(-150, -25, 300, 50), "TestButton");
    uiWin->setText("ExampleText");

    // while (true) {
        guiManager().draw();
        renderManager().getOgreWindow()->getRenderWindow()->update();
    // }

    return 0;
}

#endif
#endif