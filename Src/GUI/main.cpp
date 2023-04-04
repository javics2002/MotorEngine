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
#include <CEGUI/ImageManager.h>

using namespace me;

int main() {
    
    window();

    renderManager().createCamera("CameraDemo", 1, 10000, true, 0, Ogre::ColourValue(0, 0, 0.5));
    renderManager().setCameraInfo("CameraDemo", Ogre::Vector3f(0, 0.45, -0.8), Ogre::Vector3f(-1000, 0, 0));
    // renderManager().createNewLight("luz", Ogre::Vector3f(0, 500, 500), Ogre::Vector3f(0, -1, -1));

    renderManager().render();

    GUIManager::init();
    guiManager().loadScheme("TaharezLook.scheme");
    guiManager().setFont("DejaVuSans-10");
    CEGUI::Window* uiWin = guiManager().createWidget("TaharezLook/FrameWindow", Vector4(0.2f, 0.2f, 0.6f, 0.5f), Vector4(0, 0, 0, 0), "TestWidget");
    uiWin->setText("ExampleText");
    uiWin->setAlpha(0.5f);
    uiWin->setHorizontalAlignment(CEGUI::HA_LEFT);

    /*CEGUI::ImageManager::getSingleton().create("TaharezLook.imageset",);
    uiWin->setProperty("NormalImage", "set:Test image:TestImage");*/
    // CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

    renderManager().getOgreWindow()->getRenderWindow()->update();
    renderManager().render();
    guiManager().draw();

    while (true) {

    }

    return 0;
}

#endif
#endif