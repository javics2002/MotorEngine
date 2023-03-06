#pragma once
#ifndef _FMOD_SOUND_MANAGER
#define _FMOD_SOUND_MANAGER
#include "Utils/Singleton.h"
#include <unordered_map>

#include <iostream>
#include <stdio.h>

#include <fmod.hpp>
#include <fmod_errors.h>
#include <Utils/Vector3.h>




namespace me {
	const int MAX_CHANNELS = 36;
	typedef int CHANNEL_NUMBER;
	//typedef enum CHANNELGROUP_NAMES { EFFECTS = 0, MUSIC };

	class SoundManager : public Singleton<SoundManager>
	{

		friend Singleton<SoundManager>;
		SoundManager();
		
		std::unordered_map<FMOD::Sound*,CHANNEL_NUMBER> lastPlayedMap;
		std::unordered_map<std::string, FMOD::ChannelGroup*> channelGroupMaps;
		std::vector<FMOD::Channel*> channelsVector;
		std::vector<FMOD::ChannelGroup*> channelsGroupsVector;
		FMOD::ChannelGroup* effects, * music, *master;
		std::vector<bool> mListeners;

		FMOD::System* Sound_System = NULL;

		bool checkFMODResult(FMOD_RESULT FMODResult);

		FMOD::Channel* getChannel(FMOD::Sound* sound);

		FMOD_RESULT result;

	public:
		void systemRefresh();
		void create3DSound(const char* soundPath, FMOD::Sound*& soundHandle, int channel);
		void createNormalSound(const char* soundPath, FMOD::Sound*& soundHandle, int channel);
		void setSpeed(FMOD::Sound* soundHandle, float newSpeed);
		void setMode(FMOD::Sound* sound, int flags);
		void createChannel(const char* newChannelGroup);

		inline void setVolume(FMOD::Sound* sound, float value) {
			//TO BE IMPLEMENTED
		}
		inline float getVolume(FMOD::Sound* sound) {
			//TO BE IMPLEMENTED
		}

		void stopSound(FMOD::Sound* sound);
		void pauseSound(FMOD::Sound* sound, bool pause);
		//void playSound(FMOD::Sound* soundHandle, bool isLoop, int channelGroup, int timesLooped = -1);
		void playSound(FMOD::Sound* soundHandle, bool isLoop, const char* channelGroup, int timesLooped = -1);
		void deleteSound(FMOD::Sound* soundHandle);

		void updateListenersPosition(int index, FMOD_VECTOR listenerPos, FMOD_VECTOR listenerFW, FMOD_VECTOR listenerUP, FMOD_VECTOR listenerVel = { 0,0,0 });
		void removeListener(int index);


		void setSoundPosition(FMOD::Sound*& sound,Vector3 position);

		inline int getNextUsefulListenerIndex() {
			for (int i = 0; i < mListeners.size(); i++) {
				if (!mListeners[i])
					return i;
			}
			return -1;
		}
		
		
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

