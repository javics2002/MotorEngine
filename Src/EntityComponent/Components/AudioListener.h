#pragma once
#ifndef EC_AUDIO_LISTENER
#define EC_AUDIO_LISTENER

#include "Component.h"
#include "EntityComponent/Entity.h"


namespace me {
	class AudioListener : public me::Component
	{
	public:
		AudioListener();
		~AudioListener();

		/**
		* Update the position of the audio listener based on the position of the entity it is attached to.
		*/
		void update();

	private:
		int mListenerIndex;
	};
}

#endif // !EC_AUDIO_LISTENER