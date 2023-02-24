#pragma once
#include "Utils/Singleton.h"

namespace Ogre {
	class Root;
	class RenderWindow;
	class FileSystemLayer;
}

namespace me {
	class OgreManager : public Singleton<OgreManager> {
	public:
		void initRoot();

		void locateResources();
		void loadResources();
		bool initialiseRTShaderSystem();
	private:
	protected:
		// Root de Ogre
		Ogre::Root* mRoot;

		bool mFirstRun;

		std::string mResourceCfgPath;
		std::string mPluginCfgPath;
		std::string mOgreLogPath;
		std::string mOgreCfgPath;
		std::string mOgreResourcesPath;

		Ogre::FileSystemLayer* mFSLayer;

		/// TEMP (CARGA DE ASSETS)
		std::string mSolutionPath;
	};
}