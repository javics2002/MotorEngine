#include "GUIManager.h"
#include <Render/OgreManager.h>
#include <Render/OgreWindow.h>
#include <OgreRenderTarget.h>
#include <OgreRenderWindow.h>

CEGUI::OgreRenderer* me::GUIManager::mRenderer = nullptr;

me::GUIManager::GUIManager(const std::string& resourceDirectory)
{
	if (mRenderer == nullptr) {
		mRenderer = &CEGUI::OgreRenderer::bootstrapSystem(*static_cast<Ogre::RenderTarget*>(om().getOgreWindow()->getRenderWindow()));

		CEGUI::DefaultResourceProvider* resourceProv = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());

		// Incluir comprobación de string de directorio correcto.

		/*resourceProv->setResourceGroupDirectory("imagesets", resourceDirectory + "/imagesets/");
		resourceProv->setResourceGroupDirectory("schemes", resourceDirectory + "/schemes/");
		resourceProv->setResourceGroupDirectory("fonts", resourceDirectory + "/fonts/");
		resourceProv->setResourceGroupDirectory("layouts", resourceDirectory + "/layouts/");
		resourceProv->setResourceGroupDirectory("looknfeel", resourceDirectory + "/looknfeel/");
		resourceProv->setResourceGroupDirectory("lua_scripts", resourceDirectory + "/lua_scripts/");*/

		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	}

	mContext = &CEGUI::System::getSingleton().createGUIContext(mRenderer->getDefaultRenderTarget());
	mRoot = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "Root");
	mContext->setRootWindow(mRoot);
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
