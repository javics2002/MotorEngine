#pragma once
#ifndef _FMOD_SOUND_MANAGER
#define _FMOD_SOUND_MANAGER
#include "Utils/Singleton.h"
#include <unordered_map>

namespace me {
	class SoundManager : public Singleton<SoundManager>
	{

		friend Singleton<SoundManager>;
		SoundManager();

	public:
		void createSound();
		void playSound();
		void deleteSound();
		void createChannel();

	};
}

#endif // !_FMOD_SOUND_MANAGER

