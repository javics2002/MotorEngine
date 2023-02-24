#pragma once
#ifndef __OGRE_OGREWINDOW
#define __OGRE_OGREWINDOW

/**
*  Clase ogre que se encarga de inicializar la ventana
*
*/

#include <string>
class SDL_Window;

namespace Ogre {
	class Root;
	class RenderWindow;
	class FileSystemLayer;
}
namespace me {
	class OgreWindow {

	private:
	protected:
		std::string mWindowName;
		SDL_Window* mSdlWindow = nullptr;
		Ogre::RenderWindow* mRenderWindow = nullptr;

		//Ogre::RTShader::ShaderGenerator * mShaderGenerator; // The Shader generator instance.
		//SGTechniqueResolverListener* mMaterialMgrListener; // Shader generator material manager listener.
		void createWindow(Ogre::Root* root);
		void setWindowGrab(bool _grab);

	public:
		OgreWindow(const std::string windowName);
		~OgreWindow();

		void init(Ogre::Root* root);
		Ogre::RenderWindow* getRenderWindow();
		SDL_Window* getSdlWindow();


	};





}


#endif 