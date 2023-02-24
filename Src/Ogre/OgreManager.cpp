#include "OgreManager.h"
#include <OgreRoot.h>
#include <OgreFileSystemLayer.h>
#include <OgreConfigFile.h>
#include <iostream>

using namespace me;

void OgreManager::initRoot()
{
	mFSLayer = new Ogre::FileSystemLayer("OgreFileSystem");

	mPluginCfgPath = mFSLayer->getConfigFilePath("plugins.cfg");
	mOgreCfgPath = mFSLayer->getConfigFilePath("ogre.cfg");
	mOgreLogPath = mFSLayer->getConfigFilePath("Ogre.log");

	if (!Ogre::FileSystemLayer::fileExists(mPluginCfgPath))
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "OgreWindow::initRoot");
	if (!Ogre::FileSystemLayer::fileExists(mOgreCfgPath))
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "ogre.cfg", "OgreWindow::initRoot");
	if (!Ogre::FileSystemLayer::fileExists(mOgreLogPath))
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "Ogre.log", "OgreWindow::initRoot");

	mSolutionPath = mPluginCfgPath;    // Añadido para definir directorios relativos al de la solución 

	mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);
	mFSLayer->setHomePath(mSolutionPath);   // Para los archivos de configuración ogre. (en el bin de la solubión)
	mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);   // Quito /bin

	mRoot = new Ogre::Root(mPluginCfgPath, mOgreCfgPath, mOgreLogPath);

	if (!mRoot)
		OGRE_EXCEPT(Ogre::Exception::ERR_INVALID_CALL, "Ogre::Root", "OgreWindow::initRoot");
	mRoot->restoreConfig();
}

bool OgreManager::initialiseRTShaderSystem() {
	//if (Ogre::RTShader::ShaderGenerator::initialize())
	//{
	//	mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	//	// Core shader libs not found -> shader generating will fail.
	//	if (mRTShaderLibPath.empty())
	//		return false;
	//	// Create and register the material manager listener if it doesn't exist yet.
	//	if (!mMaterialMgrListener) {
	//		mMaterialMgrListener = new SGTechniqueResolverListener(mShaderGenerator);
	//		Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
	//	}
	//}

	return true;
}

void OgreManager::loadResources() {
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}


void OgreManager::locateResources()
{
	// load resource paths from config file
	Ogre::ConfigFile cf;

	Ogre::String resourcesPath = mFSLayer->getConfigFilePath("resources.cfg");
	if (Ogre::FileSystemLayer::fileExists(resourcesPath))
	{
		cf.load(resourcesPath);
	}
	else
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			Ogre::FileSystemLayer::resolveBundlePath(mSolutionPath + "\\media"),
			"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}

	Ogre::String sec, type, arch;
	// go through all specified resource groups
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// go through all resource paths
		for (i = settings.begin(); i != settings.end(); i++)
		{
			type = i->first;
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	// OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	// arch = genLocs.front().archive->getName();
	// type = genLocs.front().archive->getType();

	// Add locations for supported shader languages
	/*if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
		}

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
		}
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
	}*/

	/*mRTShaderLibPath = arch + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/materials", type, sec);

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/HLSL", type, sec);
	}*/


}

