#pragma once
#ifndef _FMOD_SOUND_MANAGER
#define _FMOD_SOUND_MANAGER
#include "Utils/Singleton.h"
#include "Utils/Vector3.h"
#include <unordered_map>

#include <iostream>
#include <stdio.h>

namespace FMOD {
	class Sound;
	class ChannelGroup;
	class Channel;
	class System;
}

enum FMOD_RESULT;
typedef unsigned int FMOD_MODE;

namespace me {
	const int MAX_CHANNELS = 36;
	typedef int CHANNEL_NUMBER;
	//typedef enum CHANNELGROUP_NAMES { EFFECTS = 0, MUSIC };

	/**
	SoundManager provides FMOD wrappers to manage audio creation and modulation, 
	audio channel and audio channel groups. 
	You can access the InputManager calling sm().
	*/
	class SoundManager : public Singleton<SoundManager>
	{
		friend Singleton<SoundManager>;
		SoundManager();
		//Stores audio handles linked to the last channel they where played in.
		std::unordered_map<FMOD::Sound*,CHANNEL_NUMBER> mLastPlayedMap;
		//Stores channel group names linked to their handle.
		std::unordered_map<std::string, FMOD::ChannelGroup*> mChannelGroupMaps;
		//Stores every audio channel.
		std::vector<FMOD::Channel*> mChannelsVector;
		//Basic channel groups provided by the SoundManager.
		FMOD::ChannelGroup* mEffects, * mMusic, *mMaster;
		std::vector<bool> mListeners;
		//The sound system over which every bit of audio gets created.
		FMOD::System* mSoundSystem = NULL;

		/**
		Chech if the result of any FMOD-related action is without any error.
		@param FMODResult: a flag that shows if there has been an error
		@returns A boolean representing whether there was an error or not.
		*/
		bool checkFMODResult(FMOD_RESULT FMODResult);

		/**
		Gets a channel handle via the sound that was last played on it.
		@param sound : the sound handle needed to look for a channel.
		@returns Nullptr if there is no such channel or the correspondent channel.
		*/
		FMOD::Channel* getChannel(FMOD::Sound* sound);

		/**
		Gets a group channel handle via the name it was created with.
		@param groupName : the name of the group channel.
		@returns Nullptr if there is no such group channel or the correspondent group channel.
		*/
		FMOD::ChannelGroup* getGroupChannel(std::string groupName);

		/**
		Changes the volume of a channel.
		@param group : the handle of the group channel we want to change the volume of.
		@param volume : the new value the volume will have now.
		*/
		void changeChannelVolume(FMOD::ChannelGroup* group, float volume);

		FMOD_RESULT mResult;

	public:
		/**
		Updates the sound system every step of the game loop.
		*/
		void systemRefresh();
		/**
		Creates a 3D sound.
		@param soundPath : relative path to the sound that will be loaded in the sound handle.
		@param soundHandle : the specific sound variable that will be used to play sounds.
		@param channel : the first channel the sound will be linked to.
		*/
		void create3DSound(const char* soundPath, FMOD::Sound*& soundHandle, int channel);
		/**
		Creates a normal sound.
		@param soundPath : relative path to the sound that will be loaded in the sound handle.
		@param soundHandle : the specific sound variable that will be used to play sounds.
		@param channel : the first channel the sound will be linked to.
		*/
		void createNormalSound(const char* soundPath, FMOD::Sound*& soundHandle, int channel);
		/**
		Sets the speed a certain sound wil be played at.
		@param soundHandle : the especific sound which speed will be changed.
		@param newSpeed : the new value the sound will be played at.
		*/
		void setSpeed(FMOD::Sound* soundHandle, float newSpeed);
		/**
		Sets the mode of a certain sound.
		@param sound : the especific sound which mode will be changed.
		@param newMode: the new flag the sound will be changed to.
		*/
		void setMode(FMOD::Sound* sound, FMOD_MODE newMode);
		/**
		Create a channel group if a channel with the same name doesn't already exists.
		@param newChannelGroup : the name for the new channel group.
		@return A boolean representing whether or not a new channel was indeed created.
		*/
		bool createChannelGroup(char* newChannelGroup);
		/**
		Changes the volume of a certain group channel if it exists.
		@param channelGroup : the name of the channel group.
		@param newVolume : the volume value the group channel will be changed to.
		@return A boolean representing whether or not a the volume was changed.
		*/
		bool setChannelVolume(const char* channelGroup, float newVolume);
		/**
		Changes the volume of a certain channel if it exists.
		@param sound : the sound handle needed to look for a channel.
		@param newVolume : the volume value the channel will be changed to.
		*/
		void setVolume(FMOD::Sound* sound, float newVolume);

		/**
		Checks the volume of a certain channel if it exists.
		@param sound : the sound handle needed to look for a channel.
		@return The specific float of the volume.
		*/
		float getVolume(FMOD::Sound* sound);

		/**
		Looks for a sound channel and in case that it exists, sets the pause state of that channel to "pause".
		@param sound : the sound handle needed to look for a channel.
		@param pause : the new pause value the channel will get.
		*/
		void pauseSound(FMOD::Sound* sound, bool pause);
		/**
		Sets the loopability of a certain sound  dependind on "isLoop".
		It checks for available channels to play the sound and assigns a group channel depending on the user input.
		@param soundHandle : the sound handle that will be played out.
		@param isLoop : the value of loopability that will be used to play the sound.
		@param channelGroup : the channel group where the sound will played on.
		@param timesLooped : the number of times the sound will be looped.
		By default it is set to constant loop.
		@return A boolean showing whether or not a channel group was found to play the sound.
		*/
		bool playSound(FMOD::Sound* soundHandle, bool isLoop, const char* channelGroup, int timesLooped = -1);
		/**
		Releases the dynamic memory created on runtime when creating new sounds.
		@param soundHandle : the sound handle which dynamic memory will be released.
		*/
		void deleteSound(FMOD::Sound* soundHandle);
		/**
		Updates the position of a sound listener relative to a certain sound.
		@param index : the index that refers to a certain listener.
		@param listenerPos : the position of the listener.
		@param listenerFW : 
		@param listenerUP : 
		@param listenerVel : the velocity of the listener.
		*/
		void updateListenersPosition(int index, Vector3 listenerPos, 
			Vector3 listenerFW, Vector3 listenerUP, Vector3 listenerVel = { 0,0,0 });
		/**
		Removes the listener from its vector and resets its values.
		@param index : the index that refers to a certain listener.
		*/
		void removeListener(int index);

		/**
		Sets the global position of a sound i.
		@param sound : the sound handle which position will be set.
		@param position : the value of the position of the sound.
		*/
		void setSoundPosition(FMOD::Sound*& sound, Vector3 position);

		/**
		Gets the useful listener which will be able to listen to a new sound.
		@return A integer showing whether or not a useful listener was found.
		*/
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

