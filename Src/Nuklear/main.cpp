#ifdef _DEBUG
#pragma once
#ifndef __GUI_MAIN
#define __GUI_MAIN

#include <iostream>

#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <Render/OgreManager.h>
#include <Render/OgreWindow.h>
#include <OgreRenderTarget.h>
#include <OgreRenderWindow.h>

#include "Render/Window.h"

using namespace me;

int main() {

    win();
    om().render();

    // Ogre::RenderWindow* rendTarget = om().getOgreWindow()->getRenderWindow();
    CEGUI::OgreRenderer* renderer = &CEGUI::OgreRenderer::bootstrapSystem(*static_cast<Ogre::RenderTarget*>(om().getOgreWindow()->getRenderWindow()));

    return 0;
}

#endif
#endif