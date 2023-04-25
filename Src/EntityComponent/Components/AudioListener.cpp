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

	if (mListenerIndex = -1)
		std::cout << "ERROR: Listeners vector is full\n";
}

void me::AudioListener::update()
{
	Vector3 position = mEntity->getComponent<Transform>("transform")->getPosition();
	Vector3 velocity = mEntity->getComponent<Transform>("transform")->getVelocity();
	{
		// Update the position of the audio listener in the sound manager
		soundManager().updateListenersPosition(mListenerIndex, position, {0,0,1}, {0,1,0}, velocity);
	}
}
