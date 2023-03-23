#pragma once
#ifndef __ENTITYCOMPONENT_AUDIOLISTENER
#define __ENTITYCOMPONENT_AUDIOLISTENER

#include "Component.h"

namespace me {
	class __MOTORENGINE_API  AudioListener : public me::Component
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