#include "AudioListener.h"
#include "Audio/SoundManager.h"
#include "EntityComponent/Entity.h"
#include "Transform.h"



me::AudioListener::AudioListener()
{
}

me::AudioListener::~AudioListener()
{
	soundManager().removeListener(mListenerIndex);
}

void me::AudioListener::start()
{
	// Get the next available index for a listener in the sound manager
	mListenerIndex = soundManager().getNextUsefulListenerIndex();

	if (mListenerIndex == -1)
		std::cout << "ERROR: Listeners vector is full\n";
}

void me::AudioListener::update(const double& dt)
{
	Vector3 position = mEntity->getComponent<Transform>("transform")->getPosition();
	Vector3 velocity = mEntity->getComponent<Transform>("transform")->getVelocity();
	Vector3 up = mEntity->getComponent<Transform>("transform")->up();
	Vector3 forward = mEntity->getComponent<Transform>("transform")->forward();

	Vector3 v = { (position.x - lastPosition.x)*float(dt),(position.y - lastPosition.y)*float(dt),(position.z - lastPosition.z)*float(dt)};

	lastPosition = position;

	// Update the position of the audio listener in the sound manager
	soundManager().updateListenersPosition(mListenerIndex, position, forward, up, v);
}
