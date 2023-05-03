#pragma once
#ifndef __RENDER_RENDERWINDOW
#define __RENDER_RENDERWINDOW

#include "MotorEngine/MotorEngineAPI.h"
#include <string>
typedef struct SDL_Window SDL_Window;

namespace Ogre {
	class Root;
	class RenderWindow;
	class FileSystemLayer;
}
namespace me {

	/**
	Class to create linked window between SDL_window and Ogre::RendererWindow
	*/

	class __MOTORENGINE_API RenderWindow {

	private:
	protected:
		//name to display on the window created
		std::string mWindowName;
		//Reference to SDL window created
		SDL_Window* mSdlWindow = nullptr;
		//Reference to the Ogre::Render window created
		Ogre::RenderWindow* mRenderWindow = nullptr;

		/**
		Get configuration information, Sdl window, Sdl window information 
		and create Ogre::Render window with all the information mentioned 
		It is linked window between SDL window and Ogre::Render window
		@param root:reference of Ogre::Root created by OgreManager
		*/
		void createWindow(Ogre::Root* root);
		/*Set a window input's grab mode
		void setWindowGrab(bool _grab);
		*/

	public:
		//Store windowName
		RenderWindow(const std::string windowName);
		~RenderWindow();

		/**
		Initialize linked window without automatically window created
		@param root:reference of Ogre::Root created by OgreManager
		*/
		void init(Ogre::Root* root);

		/*
		* return Ogre::Render window of linked window
		*/
		Ogre::RenderWindow* getRenderWindow();

		/*
		* return SDL window of linked window
		*/
		SDL_Window* getSdlWindow();


	};





}


#endif 