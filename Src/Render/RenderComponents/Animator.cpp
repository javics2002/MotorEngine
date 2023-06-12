#include "Animator.h"
#include "EntityComponent/Entity.h"
#include "MeshRenderer.h"
#include "Render/RenderManager.h"
#include <OgreAnimation.h>
#include <OgreEntity.h>

using namespace me;

Component* FactoryAnimator::create(Parameters& params)
{
	Animator* animator = new Animator();
	return animator;
}

void me::FactoryAnimator::destroy(Component* component)
{
	delete component;
}

Animator::Animator()
{
	
}

Animator::~Animator()
{
}

void Animator::start()
{
	mMesh = mEntity->getComponent<MeshRenderer>("meshrenderer");
	mCurrentState = nullptr;
	mAnimStatesMap = renderManager().getOgreEntity(mMesh->getName())->getAllAnimationStates();
	mStop = false;
}

void Animator::update(const double& dt)
{
	if (mCurrentState != nullptr && !mStop) {
		// Increment the animation time by the time between frames
		mCurrentState->addTime(dt);
	}
}

void Animator::setActive(bool active)
{
	// Set the enabled state for the current animation
	mCurrentState->setEnabled(active);
}

void Animator::setLoop(bool loop)
{
	// Set the loop state for the current animation
	mCurrentState->setLoop(loop);
}

std::string Animator::getCurrAnimName()
{
	// Return the name of the current animation
	return mCurrentState->getAnimationName();
}

bool Animator::isActive()
{
	// Return whether the current animation is enabled
	return mCurrentState->getEnabled();
}

bool Animator::isLoop()
{
	// Return whether the current animation is set to loop
	return mCurrentState->getLoop();
}

bool Animator::animHasEnded()
{
	// Return whether the current animation has ended
	return mCurrentState->hasEnded();
}

void Animator::playAnim(std::string anim, bool loop)
{
	if (mCurrentState != nullptr)
		mCurrentState->setEnabled(false);

	// Set the current state to the specified animation
	mCurrentState = mAnimStatesMap->getAnimationState(anim);
	// Enable the new animation state
	mCurrentState->setEnabled(true);
	// Set the loop state for the new animation state
	mCurrentState->setLoop(loop);
	// Set the time position for the new animation state to the beginning
	mCurrentState->setTimePosition(0);
}

void Animator::stopAnim()
{
	// Set the mStop flag to true to pause the current animation
	mStop = true;
}

void Animator::resumeAnim()
{
	// Set the mStop flag to false to resume the current animation
	mStop = false;
}
