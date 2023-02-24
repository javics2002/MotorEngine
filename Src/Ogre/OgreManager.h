#pragma once
#include "Utils/Singleton.h"
#include <string>

namespace Ogre {
	class Root;
	class RenderWindow;
	class FileSystemLayer;
}

namespace me {

	class OgreWindow;

	class OgreManager : public Singleton<OgreManager> {
		friend Singleton<OgreManager>;

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

		OgreWindow* ogreWindow;

		OgreManager();
		void initRoot();
		void initWindow();
		void locateResources();
		void loadResources();
		bool initialiseRTShaderSystem();

	public:

		OgreManager& operator=(const OgreManager& o) = delete;
		OgreManager(const OgreManager& o) = delete;
		~OgreManager() override;



	
	};
	/**
	This macro defines a compact way for using the singleton InputHandler, instead of
	writing InputHandler::instance()->method() we write ih().method()
	*/
	inline OgreManager& ogreM() {
		return *OgreManager::instance();
	}

}