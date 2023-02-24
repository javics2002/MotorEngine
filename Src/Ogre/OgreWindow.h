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
		Ogre::Root* mRoot;
		bool mFirstRun;

		std::string mResourceCfgPath;
		std::string mPluginCfgPath;
		std::string mOgreLogPath;
		std::string mOgreCfgPath;
		std::string mOgreResourcesPath;

		/// TEMP (CARGA DE ASSETS)
		std::string mSolutionPath;

		SDL_Window* mRenderWindow = nullptr;

		Ogre::FileSystemLayer* mFSLayer;

		//Ogre::RTShader::ShaderGenerator * mShaderGenerator; // The Shader generator instance.
		//SGTechniqueResolverListener* mMaterialMgrListener; // Shader generator material manager listener.

		void initRoot();
		void setup();
		void createWindow();
		void setWindowGrab(bool _grab);
		void locateResources();
		void loadResources();
		bool initialiseRTShaderSystem();

	public:
		OgreWindow(const std::string windowName);
		~OgreWindow();

		void init();
		Ogre::Root* getRoot();

	};





}


#endif 