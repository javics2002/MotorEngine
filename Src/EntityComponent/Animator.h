#pragma once
#ifndef __EC_ANIMATOR
#define __EC_ANIMATOR

#include "Component.h"
#include <string>
#include "Render/OgreManager.h"
#include <OgreAnimation.h>
#include "Entity.h"
#include "MeshRenderer.h"
#include <OgreEntity.h>

using namespace std;



class Animator : public me::Component
{
public:
	Animator();
	~Animator();


	void update() override;

	/**
	* Sets the Animator's active state
	* @param state Boolean value indicating whether the Animator should be active or not
	*/
	void setActive(bool state);

	/**
	* Sets the Animator's loop state
	* @param state Boolean value indicating whether the current animation should loop or not
	*/
	void setLoop(bool state);


	/**
	* Returns the name of the current animation being played
	* @return A string containing the name of the current animation
	*/
	std::string getCurrAnimName();

	/**
	* Returns the Animator's active state
	* @return A boolean value indicating whether the Animator is active or not
	*/
	bool isActive();

	/**
	* Returns the Animator's loop state
	* @return A boolean value indicating whether the current animation should loop or not
	*/
	bool isLoop();

	/*
	* Returns whether the current animation has ended or not
	* @return A boolean value indicating whether the current animation has ended
	*/
	bool animHasEnded();


	/**
	* Plays a specified animation on the Entity
	* @param anim A string containing the name of the animation to be played
	* @param loop A boolean value indicating whether the animation should loop or not
	*/
	void playAnim(std::string anim, bool loop = true);

	/**
	* Stops the current animation
	*/
	void stopAnim();

	/**
	* Resumes the current animation
	*/
	void resumeAnim();

private:
	Ogre::AnimationState* mCurrentState; // Pointer to the current animation state

	Ogre::AnimationStateSet* mAnimStatesMap; // Pointer to the animation state set

	me::MeshRenderer* mMesh = nullptr;  // Pointer to the MeshRenderer component of the Entity

	bool mStop; // Boolean value indicating whether the current animation has been stopped
};
#endif // !__EC_ANIMATOR




