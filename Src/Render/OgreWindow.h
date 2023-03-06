#pragma once
#ifndef __OGRE_OGRE_WINDOW
#define __OGRE_OGRE_WINDOW

#include <string>
class SDL_Window;

namespace Ogre {
	class Root;
	class RenderWindow;
	class FileSystemLayer;
}
namespace me {

	/**
	Class to create linked window between SDL_window and Ogre::RendererWindow
	*/

	class OgreWindow {

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
		//Set a window input's grab mode
		void setWindowGrab(bool _grab);

	public:
		//Store windowName
		OgreWindow(const std::string windowName);
		~OgreWindow();

		/**
		Initialize linked window without automatically window created
		@param root:reference of Ogre::Root created by OgreManager
		*/
		void init(Ogre::Root* root);
		//return Ogre::Render window of linked window
		Ogre::RenderWindow* getRenderWindow();
		//return SDL window of linked window
		SDL_Window* getSdlWindow();


	};





}


#endif 