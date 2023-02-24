#pragma once
#include <OgreFrameListener.h>



class OgreGame : public Ogre::FrameListener
{
	// Clase temporal para probar el funcionamiento del motor
public:
	OgreGame();
	//virtual ~OgreGame() { };   // delete -> shutdown()  

protected:
	// Ogre::Root* root;
	virtual void setup();
	virtual void shutdown();
	virtual void setupScene();

	void addSinbad(Ogre::SceneNode* mParent);

	virtual void frameRendered(const Ogre::FrameEvent& evt);

	Ogre::SceneManager* mSM = nullptr;
	// OgreBites::TrayManager* mTrayMgr = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;
	Ogre::SceneNode* mCamNode = nullptr;

	// std::vector<EntidadIG*> mEntities;
};

