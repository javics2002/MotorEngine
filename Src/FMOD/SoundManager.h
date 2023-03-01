#pragma once
#ifndef _FMOD_SOUND_MANAGER
#define _FMOD_SOUND_MANAGER
#include "Utils/Singleton.h"
#include <unordered_map>

#include <iostream>
#include <stdio.h>

#include <fmod.hpp>
#include <fmod_errors.h>



namespace me {
	const int MAX_CHANNELS = 36;
	typedef int channelNumber;
	typedef enum CHANNELGROUP_NAMES { EFFECTS = 0, MUSIC };

	class SoundManager : public Singleton<SoundManager>
	{

		friend Singleton<SoundManager>;
		SoundManager();
		
		std::unordered_map<FMOD::Sound*,channelNumber> lastPlayedMap;
		std::vector<FMOD::Channel*> channelsVector;
		std::vector<FMOD::ChannelGroup*> channelsGroupsVector;
		FMOD::ChannelGroup* effects, * music, *master;

		FMOD::System* Sound_System = NULL;

		bool checkFMODResult(FMOD_RESULT FMODResult);

		FMOD_RESULT result;

	public:
		void create3DSound(const char* soundPath, FMOD::Sound* soundHandle, int channel);
		void createNormalSound(const char* soundPath, FMOD::Sound* soundHandle, int channel);
		void playSound(FMOD::Sound* soundHandle, bool isLoop, int channelGroup, int timesLooped = -1);
		void deleteSound(FMOD::Sound* soundHandle);
		void setSpeed(FMOD::Sound* soundHandle, float newSpeed);

		//void createChannel(); Sería necesario??
		
	};

	/**
	This macro defines a compact way for using the singleton PhysicsManager, instead of
	writing SoundManager::instance()->method() we write sm().method()
	*/
	inline SoundManager& sm() {
		return *SoundManager::instance();
	}
}

#endif // !_FMOD_SOUND_MANAGER

