#pragma once
#ifndef __OGRE_MANAGER
#define __OGRE_MANAGER

#include "Utils/Singleton.h"
#include <unordered_map>
#include <string>
#include <OgreColourValue.h>


namespace Ogre {
	class Root;
	class RenderWindow;
	class FileSystemLayer;
	class SceneManager;
	class SceneNode;
	class Quaternion;
	template<int dism, typename T>
	class Vector;
	typedef Vector<3, float> Vector3f;

	namespace RTShader {
		class ShaderGenerator;
	}
	class TextAreaOverlayElement;
}

namespace me {

	class OgreWindow;
	class OgreCamera;
	class OgreMesh;
	class OgreParticleSystem;
	class SGTechniqueResolverListener;
	class OverlayManager;

	/**
	OgreManager initialize Ogre (Root, RTShaderSystem, SceneManager, RenderWindow), 
	locate and load resources (from resource.cfg)
	and handle the creation of camera, light, mesh
	You can access the OgreManager just calling om().
	*/
	class OgreManager : public Singleton<OgreManager> {
		friend Singleton<OgreManager>;
		/**
		Initialize Ogre (Root, RTShaderSystem, SceneManager, RenderWindow),locate and load Resource
		*/
		OgreManager();

	private:
	protected:
		// Root de Ogre
		Ogre::Root* mRoot;
		//SceneManager de Ogre
		Ogre::SceneManager* mSM = nullptr;

		// TEMPORAL VALUE FOR ANIMATION HITO1
		Ogre::AnimationState* ogreAnimState;

		/**
		Path of the "resource.cfg"
		Add all resources (mesh, zip, particles, material, animation) to the subfolder of Asset
		And they are accessed by putting paths in "resource.cfg" like this:
			Zip= ../../Assets/packs/Sinbad.zip
			FileSystem=../../Assets/Main
		Be careful, our working directory is "Exe/Main/", 
		so we have to go to the above directory 2 times to access the "Assets" directory.
		*/
		std::string mResourceCfgPath;

		/**
		Path of the "plugins.cfg"
		Add all necessary Ogre plugins in "plugins.cfg" like this:
			Plugin=Codec_STBI
		Remember to add all the .dll of the written plugins
		*/
		std::string mPluginCfgPath;


		OverlayManager* mOverlayManager;


		/**
		Path of the "Ogre.cfg"
		configuration file where it indicates all the configurations 
		proposed for "Renderer DirectX11"
		*/
		std::string mOgreCfgPath;

		//Ogre fileSystem
		Ogre::FileSystemLayer* mFSLayer;

		//Ogre ShaderGenerator
		Ogre::RTShader::ShaderGenerator* mShaderGenerator;

		//Ogre Material Manager Listener
		SGTechniqueResolverListener* mMaterialMgrListener;

		//Path pointing to "/Main/x64/debug"
		std::string mSolutionPath;

		//Reference to OgreWindow class
		OgreWindow* mOgreWindow;

		//Store camera name to ogreCamera
		std::unordered_map<std::string, OgreCamera*> mCameras;			//Pairs each cameras with its name
		//Store mesh name to ogreMesh
		std::unordered_map<std::string, OgreMesh*> mMeshes;			//Pairs each mesh with its name
		//Store mesh name to ogreParticleSystem
		std::unordered_map<std::string, OgreParticleSystem*> mParticles;			//Pairs each mesh with its name
		/**
		initializes FileSystem, find m_Paths and initialize Ogre::Root
		*/
		void initRoot();
		/**
		Creates OgreWindow (RenderWindow)
		*/
		void initWindow();

		/*
		Find mResourcePath and add all written resources to Ogre::ResourceGroupManager
		*/
		void locateResources();
		/**
		Call Ogre::ResourceGroupManager to load added resources
		*/
		void loadResources();
		/**
		initialize RTShaderSystem (Shader Generator) and add Ogre:: Material Manager Listener
		*/
		bool initialiseRTShaderSystem();

		/**
		@param name: Name of the camera
		@return OgreCamera: that was created with this name 
		@return nullptr: if it doesn't exist
		*/
		OgreCamera* getCamera(std::string name);

		/**
		@param name: Name of the mesh
		@return OgreMesh: that was created with this name
		@return nullptr: if it doesn't exist
		*/
		OgreMesh* getMesh(std::string name);

		/**
		@param name: Name of the particle
		@return OgreParticleSystem: that was created with this name
		@return nullptr: if it doesn't exist
		*/
		OgreParticleSystem* getParticle(std::string name);

	public:
		OgreManager&operator=(const OgreManager&o) = delete;
		OgreManager(const OgreManager&o) = delete;
		~OgreManager() override;

		/**
		Create the camera that is a child of another Ogre::SceneNode with this name and store it
		@param name: name of camera
		@param parentName: name of parent Ogre::SceneNode
		@param nearDist: near clipping plane distancia 
		@param farDist: far clipping plane distancia 
		@param autoRadio: if viewport calculate aspect radio automatically
		@param zOrder: relative order of viewport
		@return false: if renamed
		@return true: if succeed
		*/
		bool createCamera(std::string name, std::string parentName, int nearDist, int farDist, bool autoRadio, int zOrder, Ogre::ColourValue color = Ogre::ColourValue(0, 0, 0, 1));
		
		/**
		Create the camera with this name and store it
		@param name: name of camera
		@param nearDist: near clipping plane distancia
		@param farDist: far clipping plane distancia
		@param autoRadio: if viewport calculate aspect radio automatically
		@param zOrder: relative order of viewport
		@return false: if renamed
		@return true: if succeed
		*/
		//bool createCamera(std::string name, int nearDist, int farDist, bool autoRadio, int zOrder, Ogre::ColourValue color);
		
		bool createCamera(std::string name, int nearDist, int farDist, bool autoRadio, int zOrder, Ogre::ColourValue color = Ogre::ColourValue(0, 0, 0, 1));

		/**
		Set location and direction to the camera with this name
		@param name: name of camera
		@param pos: position of camera
		@param look: camera look at
		@return false: if it doesn't exist
		@return true: if succeed
		*/
		bool setCameraInfo(std::string name, const Ogre::Vector3f &pos, const Ogre::Vector3f &look);

		/**
		Set dimension to the viewport of the camera with this name
		@param name: name of camera
		@param left: left point of viewport in range 0.0 to 1.0
		@param top: top point of viewport in range 0.0 to 1.0
		@param width: width of viewport in range 0.0 to 1.0
		@param height: height of viewport in range 0.0 to 1.0
		@return false: if it doesn't exist
		@return true: if succeed
		*/
		bool setViewportDimension(std::string name, float left, float top, float width, float height);

		//destroy OgreCamera created 
		void destroyCamera(std::string name);

		/**
		Create the light with this name
		@param name: name of light
		@param pos: position of light
		@param dir: direction of light
		*/
		void createNewLight(std::string name, const Ogre::Vector3f &pos, const Ogre::Vector3f &dir);
		
		/**
		Create the ogreMesh with this name 
		@param name: name of Ogre::SceneNode &&unordered_map
		@param nameMesh: name of file (xxx.mesh)
		@return false: if renamed
		@return true: if succeed
		*/
		bool createMesh(std::string name, std::string nameMesh);

		/**
		Set Transform info to the mesh with this name (for static object)
		@param name: name of ogreMesh
		@param pos: position of ogreMesh
		@param scale: scale of ogreMesh
		@return false: if it doesn't exist
		@return true: if succeed		
		*/
		bool setMeshTransform(std::string name, const Ogre::Vector3f &pos, const Ogre::Vector3f &scale);
		bool setMeshTransform(std::string name, const Ogre::Vector3f &pos, const Ogre::Vector3f &scale, const Ogre::Quaternion&rot);
		//set position info to the mesh with this name
		bool setMeshPosition(std::string name, const Ogre::Vector3f &pos);
		//set scale info to the mesh with this name
		bool setMeshScale(std::string name, const Ogre::Vector3f &scale);
		//set rotation info to the mesh with this name
		bool setMeshRotation(std::string name,Ogre::Quaternion rot);

		//set material to the mesh with this name
		bool setMeshMaterial(std::string name, std::string nameMaterial);

		//destroy OgreMesh created 
		void destroyMesh(std::string name);

		/**
		Create the ogreParticleSystem with this name
		@param name: name of Ogre::SceneNode &&unordered_map
		@param nameParticle: name of partcile system that is written int ParticleResource.particle
		@return false: if renamed
		@return true: if succeed
		*/
		bool createParticle(std::string name, std::string nameMesh);
		/**
		Set Transform info to the particle with this name (for static object)
		@param name: name of ogreParticleSystem
		@param pos: position of ogreParticleSystem
		@param scale: scale of ogreParticleSystem
		@return false: if it doesn't exist
		@return true: if succeed
		*/
		bool setParticleTransform(std::string name, const Ogre::Vector3f& pos, const Ogre::Vector3f& scale);
		bool setParticleTransform(std::string name, const Ogre::Vector3f& pos, const Ogre::Vector3f& scale, const Ogre::Quaternion& rot);
		//set position info to the particle with this name
		bool setParticlePosition(std::string name, const Ogre::Vector3f& pos);
		//set scale info to the particle with this name
		bool setParticleScale(std::string name, const Ogre::Vector3f& scale);
		//set rotation info to the particle with this name
		bool setParticleRotation(std::string name, Ogre::Quaternion rot);

		//set emitting state to the particle with this name
		bool setParticleEmitting(std::string name, bool emitted);

		
		/**
		@param name: name of node
		@return Ogre::SceneNodo created with this name and it is in root node
		*/
		Ogre::SceneNode* createNode(std::string name);
		/**
		@param name: name of node
		@param parent: name of parent node
		@return Ogre::SceneNodo created with this name and it is child node of another node
		*/
		Ogre::SceneNode* createChildNode(std::string name, std::string parent);

		/**
		Returns a pointer to the OgreWindow used for rendering.
		@return The Render Window
		*/
		OgreWindow* getOgreWindow();

		/**
		Returns a pointer to the Root SceneNode.
		@return returns the root scene node
		*/
		Ogre::SceneNode* getRootSceneNode();

		/**
		Example scene where rendering a sinbad with 2 camera,viewport
		*/
		void scene1();

		/**
		Render one frame of Ogre::Root -> current scene manager
		*/
		void render();

		/**
		Return the Ogre::Entity asociated
		*/
		Ogre::Entity* getOgreEntity(std::string name);


		//Text UI
		Ogre::TextAreaOverlayElement* createOverlayElement();
		/*Getter for scene manager
		*/
		Ogre::SceneManager* getSceneManager();


	};

	/**
		This macro defines a compact way for using the singleton OgreManager, instead of
		writing OgreManager::instance()->method() we write om().method()
	*/
	inline OgreManager&om() {
		return *OgreManager::instance();
	}

}
#endif