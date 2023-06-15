#include "AudioListener.h"
#include "Audio/SoundManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Transform.h"
#include "MotorEngine/MotorEngineError.h"
#include "MotorEngine/SceneManager.h"


me::Component* me::FactoryAudioListener::create(Parameters& params)
{
	AudioListener* audioListener = new AudioListener();

	return audioListener;
}

void me::FactoryAudioListener::destroy(Component* component)
{
	delete component;
}

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

#ifdef _DEBUG
	if (mListenerIndex == -1)
		std::cout << "ERROR: Listeners vector is full\n";
#endif // _DEBUG
}

void me::AudioListener::update(const double& dt)
{
	if (!mEntity->getComponent<Transform>("transform")) {
		errorManager().throwMotorEngineError("AudioListener error", "An entity doesn't have transform component");
		sceneManager().quit();
	}


	Vector3 position = mEntity->getComponent<Transform>("transform")->getPosition();
	Vector3 velocity = mEntity->getComponent<Transform>("transform")->getVelocity();
	Vector3 up = mEntity->getComponent<Transform>("transform")->up();
	Vector3 forward = mEntity->getComponent<Transform>("transform")->forward();

	Vector3 v = { (position.x - lastPosition.x)*float(dt),(position.y - lastPosition.y)*float(dt),(position.z - lastPosition.z)*float(dt)};

	lastPosition = position;

	// Update the position of the audio listener in the sound manager
	soundManager().updateListenersPosition(mListenerIndex, position, forward, up, v);
}
