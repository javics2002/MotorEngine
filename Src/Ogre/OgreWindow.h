#pragma once
#ifndef __OGRE_OGREWINDOW
#define __OGRE_OGREWINDOW

/**
*  Clase ogre que se encarga de inicializar la ventana
*
*/

#include <string>
class FileSystemLayer;
class SDL_Window;

namespace Ogre {
	class Root;
	class RenderWindow;
}
namespace me {
	class OgreWindow {

	private:
	protected:
		std::string mWindowName;
		Ogre::Root* mRoot;
		bool mFirstRun;
		std::string mResourceCfgPath;
		std::string mPluginCfgPath;
		std::string mOgreLogPath;
		std::string mOgreCfgPath;

		Ogre::RenderWindow* mRenderWindow = nullptr;
		SDL_Window* mSdlWindow = nullptr;

		//Ogre::RTShader::ShaderGenerator * mShaderGenerator; // The Shader generator instance.
		//SGTechniqueResolverListener* mMaterialMgrListener; // Shader generator material manager listener.

		void initRoot();
		void setup();
		void createWindow();

	public:
		OgreWindow(const std::string windowName);
		~OgreWindow();

		void init();


	};





}


#endif 