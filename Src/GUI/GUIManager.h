#pragma once
#ifndef __GUI_MANAGER
#define __GUI_MANAGER

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "Utils/Singleton.h"
#include "Utils/Vector4.h"

namespace me {

	/**
	GUIManager initializes CEGUI (Renderer, System, etc.),
	and handles the creation and layout of GUI elements.
	You can access the GUIManager by simply calling guim().
	*/
	class GUIManager : public Singleton<GUIManager>
	{
		friend Singleton<GUIManager>;

		/**
		Initializes CEGUI renderer and system, only if it has not been initialized before.
		Takes into account the current window, so initialize the RenderManager first.
		@param resourceDirectory Directory of the fonts, images, etc. folders.
		*/
		GUIManager(const std::string& resourceDirectory = "../../../../Assets/GUI");

	private:
		static CEGUI::OgreRenderer* mRenderer;
		CEGUI::GUIContext* mContext = nullptr;
		CEGUI::Window* mRoot = nullptr;

	public:
		GUIManager& operator=(const GUIManager& o) = delete;
		GUIManager(const GUIManager& o) = delete;
		~GUIManager() override;

		/**
		Draws the GUI elements on screen. Must be called after the rendering of all other scene objects.
		*/
		void draw();

		/**
		Loads the scheme from a .scheme file.
		@param schemeFile path to the scheme file, taking into account the resource path from initialization.
		*/
		void loadScheme(const std::string& schemeFile);

		/**
		Loads the scheme from a .font file. Do not include ".font" in the name.
		@param schemeFile path to the font file, taking into account the resource path from initialization.
		*/
		void setFont(const std::string& fontFile);

		/**
		Creates a new Widget, using the given .scheme, setting its position and size in relation to its parent or pizel size (both can also be combined), and optionally giving it a name.
		@param type Type of the new Widget (PushButton, etc.).
		@param destRectPercentage Position and Size of the new Widget in relation to the parent, as PositionX, PositionY, SizeX, SizeY.
		@param destRectPixels Position and Size of the new Widget in pixels, as PositionX, PositionY, SizeX, SizeY.
		@param name Optional name given to the widget. Empty string by default.
		*/
		CEGUI::Window* createWidget(const std::string& type, const Vector4& destRectPercentage, const Vector4& destRectPixels, const std::string& name = "");

		/**
		Sets the Destination Rect of a given Widget.
		@param widget Target Widget.
		@param destRectPercentage Position and Size of the new Widget in relation to the parent, as PositionX, PositionY, SizeX, SizeY.
		@param destRectPixels Position and Size of the new Widget in pixels, as PositionX, PositionY, SizeX, SizeY.
		*/
		void setWidgetDestRect(CEGUI::Window* widget, const Vector4& destRectPercentage, const Vector4& destRectPixels);


		// -------------- Getters ---------------

		/**
		Returns a pointer to the CEGUI OgreRenderer.
		@return returns the renderer.
		*/
		CEGUI::OgreRenderer* getOgreRenderer();

		/**
		Returns a pointer to the CEGUI GUIContext.
		@return returns the context.
		*/
		CEGUI::GUIContext* getContext();
	};

	/**
		This macro defines a compact way for using the singleton GUIManager, instead of
		writing GUIManager::instance()->method() we write guim().method()
	*/
	inline GUIManager& guim() {
		return *GUIManager::instance();
	}
}

#endif