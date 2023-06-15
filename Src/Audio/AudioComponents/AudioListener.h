#pragma once
#ifndef __ENTITYCOMPONENT_AUDIOLISTENER
#define __ENTITYCOMPONENT_AUDIOLISTENER

#include "EntityComponent/Component.h"
#include "EntityComponent/FactoryComponent.h"
#include "Utils/Vector3.h"

namespace FMOD {
	class Sound;
	class FMOD_VECTOR;
}

namespace me {
	class SoundManager;

	//Creates and destroys AudioListener components
	class FactoryAudioListener : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};


	/**
	An Entity with this component will output the audio it listens
	where it is located.
	*/
	class __MOTORENGINE_API  AudioListener : public me::Component
	{
	public:
		AudioListener();
		~AudioListener();

		void start() override;

		/**
		* Update the position of the audio listener based on the position of the entity it is attached to.
		*/
		void update(const double& dt) override;

	private:
		Vector3 position ;
		Vector3 lastPosition = { 0,0,0 };
		int mListenerIndex;
	};
}

#endif // !EC_AUDIO_LISTENER