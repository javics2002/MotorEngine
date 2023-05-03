#pragma once
#ifndef __RENDER_MANAGER
#define __RENDER_MANAGER

#include "MotorEngine/MotorEngineAPI.h"
#include "Utils/Singleton.h"
#include "Utils/Vector4.h"
#include "Utils/Vector2.h"
#include <unordered_map>
#include <string>

namespace Ogre {
	class Root;
	class SceneManager;
	class Entity;
	class SceneNode;
	class OverlayManager;
	class OverlaySystem;
	class FileSystemLayer;
	class Light;

	namespace RTShader {
		class ShaderGenerator;
	}
}

namespace me {
	class RenderWindow;
	class RenderCamera;
	class RenderMesh;
	class RenderUISprite;
	class SGTechniqueResolverListener;


	/**
	OgreManager initialize Ogre (Root, RTShaderSystem, SceneManager, RenderWindow), 
	locate and load resources (from resource.cfg)
	and handle the creation of camera, light, mesh
	You can access the OgreManager just calling om().
	*/
	class __MOTORENGINE_API RenderManager : public Singleton<RenderManager> {
		friend Singleton<RenderManager>;
		/**
		Initialize Ogre (Root, RTShaderSystem, SceneManager, RenderWindow),locate and load Resource
		*/
		RenderManager();

	protected:
		// Root de Ogre
		Ogre::Root* mRoot;
		//SceneManager de Ogre
		Ogre::SceneManager* mSM;

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

		/**
		Manages Overlay objects, parsing them from .overlay files and 
		storing a lookup library of them.
		Also manages the creation of OverlayContainers and OverlayElements, 
		used for non-interactive 2D elements such as HUDs.
		*/
		Ogre::OverlayManager* mOverlayManager;

		/**
		This class simplify initialization / finalization of the overlay system.
		Before you create a concrete instance of the OverlaySystem the OGRE::Root 
		must be created but not initialized. In the ctor all relevant systems are 
		created and registered. The dtor must be called before you delete OGRE::Root. 
		To make the overlays visible (= render into your viewports) you have to 
		register this instance as a RenderQueueListener in your scenemanager(s).
		*/
		Ogre::OverlaySystem* mOverlaySystem;

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

		//Reference to RenderWindow class
		RenderWindow* mOgreWindow;

		std::unordered_map<std::string, RenderCamera*> mCameras;		//Pairs each cameras with its name
		std::unordered_map<std::string, RenderMesh*> mMeshes;			//Pairs each mesh with its name
		std::unordered_map<std::string, RenderUISprite*> mSprites;			//Pairs each UISprite with its name
		std::unordered_map<std::string, Ogre::Light*> mLights;			//Pairs each mesh with its name

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

		//Destroy RTShaderSystem (Shader Generator) and add Ogre:: Material Manager Listener
		void destroyRTShaderSystem();

		/**
		@param name: Name of the camera
		@return OgreCamera: that was created with this name 
		@return nullptr: if it doesn't exist
		*/
		RenderCamera* getCamera(std::string name);

		/**
		@param name: Name of the sprite
		@return RenderUISprite: that was created with this name
		@return nullptr: if it doesn't exist
		*/
		RenderUISprite* getUISprite(std::string name);


		/**
		@param name: Name of the mesh
		@return OgreMesh: that was created with this name
		@return nullptr: if it doesn't exist
		*/
		RenderMesh* getMesh(std::string name);

	public:
		RenderManager&operator=(const RenderManager&o) = delete;
		RenderManager(const RenderManager&o) = delete;
		~RenderManager() override;

		/**
		Create the camera that is a child of another Ogre::SceneNode with this name and store it
		@param name: name of camera
		@param parentName: name of parent Ogre::SceneNode
		@param nearDist: near clipping plane distancia 
		@param farDist: far clipping plane distancia 
		@param autoRatio: if viewport calculate aspect radio automatically
		@param zOrder: relative order of viewport
		@return false: if renamed
		@return true: if succeed
		*/
		bool createCamera(std::string name, std::string parentName, int nearDist, 
			int farDist, bool autoRatio, int zOrder, Vector4 colour = Vector4(0, 0, 0, 1));
		
		/**
		Create the camera with this name and store it
		@param name: name of camera
		@param nearDist: near clipping plane distancia
		@param farDist: far clipping plane distancia
		@param autoRatio: if viewport calculate aspect ratio automatically
		@param zOrder: relative order of viewport
		@return false: if renamed
		@return true: if succeed
		*/
		bool createCamera(std::string name, float nearDist, float farDist, bool autoRatio,
			int zOrder, Vector4 colour = Vector4(0, 0, 0, 1));

		/**
		Set location and direction to the camera with this name
		@param name: name of camera
		@param pos: position of camera
		@param look: camera look at
		@return false: if it doesn't exist
		@return true: if succeed
		*/
		bool setCameraInfo(std::string name, const Vector3& pos, const Vector3& look);

		/*
		Locks camera orientation in Y Axis
		@param bFixed: lock boolean
		*/
		bool setCameraFixedY(std::string name, bool bFixed);

		/**
		*Enable or disable the overlay for a camera's viewport
		*@param name: the name of the camera
		*@param enabled: whether the overlay should be enabled (true) or disabled (false)
		*@return true if the operation succeeded, false otherwise
		*/
		bool setViewportOverlayEnabled(std::string name, bool enabled);

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

		/**
		Destroy OgreCamera
		@param name: name of camera
		*/
		void destroyCamera(std::string name);

		/**
		Create the light with this name
		@param name: name of light
		@param pos: position of light
		@param dir: direction of light
		@param color: color of light
		*/
		void createNewLight(std::string name, const Vector3& pos, const Vector3& dir,
			const Vector3& color);

		/**
		Destroy Light
		@param name: name of light
		*/
		void destroyLight(std::string name);

		/**
		Set the ambient light of this scene
		@param color: color of ambient light
		*/
		void setAmbientLight(const Vector3& color);
		
		/**
		Create the ogreMesh with this name 
		@param name: name of Ogre::SceneNode &&unordered_map
		@param nameMesh: name of file (xxx.mesh)
		@return false: if renamed
		@return true: if succeed
		*/
		bool createMesh(std::string name, std::string nameMesh);

		/**
		Creates a 2D sprite in the overlay.
		@param name: Name of Ogre::OverlayElement &&unordered_map
		@param nameMesh: Name of file (xxx.png)
		@return false: if renamed
		@return true: if succeed
		*/
		bool createSprite(std::string name, std::string nameMesh, int zOrder);

		/**
		Set Transform info to the mesh with this name (for static object)
		@param name: name of ogreMesh
		@param pos: position of ogreMesh
		@param scale: scale of ogreMesh
		@return false: if it doesn't exist
		@return true: if succeed		
		*/
		bool setMeshTransform(std::string name, Vector3 pos, Vector3 scale);


		/**
		Set Transform info to the mesh with this name (for static object)
		@param name: name of ogreMesh
		@param pos: position of ogreMesh
		@param scale: scale of ogreMesh
		@param rot: rotation of ogreMesh
		@return false: if it doesn't exist
		@return true: if succeed
		*/
		bool setMeshTransform(std::string name, Vector3 pos, Vector3 scale, Vector4 rot);
		
		/**
		Set position info to the mesh with this name
		@param name: name of ogreMesh
		@param pos: position of ogreMesh
		@return false: if it doesn't exist
		@return true: if succeed
		*/
		bool setMeshPosition(std::string name, Vector3 pos);
		/**
		Set scale info to the mesh with this name
		@param name: name of ogreMesh
		@param scale: scale of ogreMesh
		@return false: if it doesn't exist
		@return true: if succeed
		*/
		bool setMeshScale(std::string name, Vector3 scale);
		/**
		Set rotation info to the mesh with this name
		@param name: name of ogreMesh
		@param rot: rotation of ogreMesh
		@return false: if it doesn't exist
		@return true: if succeed
		*/
		bool setMeshRotation(std::string name, Vector4 rot);
		/**
		Set material to the mesh with this name
		@param name: name of ogreMesh
		@param nameMaterial: new material name for ogreMesh
		@return false: if it doesn't exist
		@return true: if succeed
		*/
		bool setMeshMaterial(std::string name, std::string nameMaterial);
		/**
		Active the mesh from scene
		@param name: name of ogreMesh
		*/
		void activeMesh(std::string name);

		/**
		Desactive the mesh from scene
		@param name: name of ogreMesh
		*/
		void desactiveMesh(std::string name);

		
		/**
		Destroy OgreMesh created 
		@param name: name of ogreMesh
		*/
		void destroyMesh(std::string name);

		/**
		Set UITransform info of the UISprite with this name (for static object)
		@param name: name of UISprite
		@param pos: position of UISprite
		@param scale: scale of UISprite
		@param rot: rotation of UISprite
		@return false: if it doesn't exist
		@return true: if succeeded	
		*/
		bool setUISpriteTransform(std::string name, Vector2 pos, Vector2 scale, float rot);

		/**
		Set position info to the mesh with this name
		@param name: name of UISprite
		@param pos: position of UISprite
		@return false: if it doesn't exist
		@return true: if succeeded
		*/
		bool setUISpritePosition(std::string name, Vector2 pos);
		/**
		Set scale info to the mesh with this name
		@param name: name of UISprite
		@param scale: scale of UISprite
		@return false: if it doesn't exist
		@return true: if succeeded
		*/
		bool setUISpriteScale(std::string name, Vector2 scale);
		/**
		Set rotation info to the mesh with this name
		@param name: name of UISprite
		@param rot: rotation of UISprite
		@return false: if it doesn't exist
		@return true: if succeeded
		*/
		bool setUISpriteRotation(std::string name, float rot);

		/**
		Set material to the mesh with this name
		@param name: name of UISprite
		@param nameMaterial: maetrial name for UISprite
		@return false: if it doesn't exist
		@return true: if succeeded
		*/
		bool setUISpriteMaterial(std::string name, std::string nameMaterial);

		/**
		Destroy UISprite created
		@param name: name of UISprite to destroy
		*/
		void destroyUISprite(std::string name);
		
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
		RenderWindow* getOgreWindow();

		/**
		Returns a pointer to the Root SceneNode.
		@return returns the root scene node
		*/
		Ogre::SceneNode* getRootSceneNode();


		/**
		Render one frame of Ogre::Root -> current scene manager
		*/
		void render();

		/**
		Return the Ogre::Entity asociated
		*/
		Ogre::Entity* getOgreEntity(std::string name);

		/*
		Getter for scene manager
		*/
		Ogre::SceneManager* getSceneManager();

		/*
		Getter for OgreOverlayManager
		*/	
		Ogre::OverlayManager* getOgreManager();


	};

	/**
		This macro defines a compact way for using the singleton OgreManager, instead of
		writing OgreManager::instance()->method() we write om().method()
	*/
	inline RenderManager& renderManager() {
		return *RenderManager::Instance();
	}

}
#endif