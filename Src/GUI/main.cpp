#ifdef _DEBUG
#pragma once
#ifndef __GUI_MAIN
#define __GUI_MAIN

#include <iostream>


#include "GUI/GUIManager.h"
#include "Render/Window.h"
#include <Render/OgreManager.h>

using namespace me;

int main() {

    win();
    om().render();

    GUIManager::init("");
    guim().loadScheme("TaharezLook.scheme");
    guim().setFont("DejaVuSans-10");
    guim().createWidget("TaharezLook/Button", Vector4(0.5f, 0.5f, 0.1f, 0.05f), Vector4(), "TestButton");

    while (true) {
        guim().draw();
    }

    delete GUIManager::instance();

    //CEGUI::OgreRenderer* renderer = &CEGUI::OgreRenderer::bootstrapSystem(*static_cast<Ogre::RenderTarget*>(om().getOgreWindow()->getRenderWindow()));

    //CEGUI::GUIContext* context = &CEGUI::System::getSingleton().createGUIContext(renderer->getDefaultRenderTarget());

    //CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    //context->getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

    //CEGUI::Window* root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "Root");
    //context->setRootWindow(root);

    //CEGUI::Font* defaultFont = &CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
    //context->setDefaultFont(defaultFont);

    //CEGUI::Window* testChild = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button", "TestButton");
    //root->addChild(testChild);

    //testChild->setArea(CEGUI::UVector2(cegui_reldim(0.25f), cegui_reldim(0.25f)), CEGUI::USize(cegui_reldim(0.5f), cegui_reldim(0.5f)));
    //testChild->setMaxSize(CEGUI::USize(cegui_reldim(1.0f), cegui_reldim(1.0f)));
    //testChild->setMinSize(CEGUI::USize(cegui_reldim(0.1f), cegui_reldim(0.1f)));

    //while (true) {
    //    renderer->beginRendering();
    //    context->draw();
    //    renderer->endRendering();
    //}

    //CEGUI::System::getSingleton().destroyGUIContext(*context);

    return 0;
}

#endif
#endif