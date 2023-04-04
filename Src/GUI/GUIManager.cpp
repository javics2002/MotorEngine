#include "GUIManager.h"
#include <Render/RenderManager.h>
#include <Render/RenderWindow.h>
#include <OgreRenderTarget.h>
#include <OgreRenderWindow.h>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <CEGUI/Logger.h>
#include <CEGUI/DefaultLogger.h>

CEGUI::OgreRenderer* me::GUIManager::mRenderer = nullptr;

me::GUIManager::GUIManager()
{
	if (mRenderer == nullptr) {
		mRenderer = &CEGUI::OgreRenderer::bootstrapSystem(*static_cast<Ogre::RenderTarget*>(renderManager().getOgreWindow()->getRenderWindow()));

		CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
		CEGUI::Scheme::setDefaultResourceGroup("Schemes");
		CEGUI::Font::setDefaultResourceGroup("Fonts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
		CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
		// CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	}

	mContext = &CEGUI::System::getSingleton().createGUIContext(mRenderer->getDefaultRenderTarget());
	mRoot = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "Root");
	mRoot->setUsingAutoRenderingSurface(false);
	mContext->setRootWindow(mRoot);
	mRenderer->setUsingShaders(true);
}

me::GUIManager::~GUIManager()
{
	CEGUI::System::getSingleton().destroyGUIContext(*mContext);
}

void me::GUIManager::draw()
{
	mRenderer->beginRendering();
	mContext->draw();
	mRenderer->endRendering();
}

void me::GUIManager::loadScheme(const std::string& schemeFile)
{
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void me::GUIManager::setFont(const std::string& fontFile)
{
	CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
	mContext->setDefaultFont(fontFile);
}

CEGUI::Window* me::GUIManager::createWidget(const std::string& type, const Vector4& destRectPercentage, const Vector4& destRectPixels, const std::string& name)
{
	CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	mRoot->addChild(newWindow);
	setWidgetDestRect(newWindow, destRectPercentage, destRectPixels);
	return newWindow;
}

void me::GUIManager::setWidgetDestRect(CEGUI::Window* widget, const Vector4& destRectPercentage, const Vector4& destRectPixels)
{
	widget->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPercentage.x, destRectPixels.x), CEGUI::UDim(destRectPercentage.y, destRectPixels.y)));
	widget->setSize(CEGUI::USize(CEGUI::UDim(destRectPercentage.z, destRectPixels.z), CEGUI::UDim(destRectPercentage.w, destRectPixels.w)));
}


// --------- Getters ----------

CEGUI::OgreRenderer* me::GUIManager::getOgreRenderer()
{
	return mRenderer;
}

CEGUI::GUIContext* me::GUIManager::getContext()
{
	return mContext;
}
