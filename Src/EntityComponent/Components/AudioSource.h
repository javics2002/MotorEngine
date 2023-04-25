#pragma once
#ifndef __ENTITYCOMPONENT_AUDIOSOURCE
#define __ENTITYCOMPONENT_AUDIOSOURCE

#include <string>

#include "Component.h"
#include "Transform.h"
#include "Audio/SoundManager.h"


namespace FMOD {
	class Sound;
}

namespace me {
	class SoundManager;
	/**
	Plays an audio file in the scene. AudioListeners within range
	will hear it with the intensity based in their position in the scene. 
	*/
	class __MOTORENGINE_API AudioSource : public Component
	{
	public:

		/*
		Default constructor
		*/
		AudioSource();
		~AudioSource();

		void start();

		void update();

		/**
		* Play the audio.
		*/
		void play();

		/**
		* Stop the audio.
		*/
		void stop();

		/**
		* Pause the audio.
		*/
		void pause();

		/**
		* Resume playing the audio after it has been paused.
		*/
		void resume();

		/**
		* Check if the audio is currently playing.
		* @return True if the audio is playing, false otherwise.
		*/
		bool isPlaying();


		/**
		* Set the volume of the audio.
		* @param value The new volume value.
		*/
		inline void setVolume(float value) {
			mVolume = value;
			soundManager().setVolume(mSoundName, value);
		}

		/**
		* Set the speed of the audio.
		* @param value The new speed value.
		*/
		inline void setSpeed(float value) {
			mSpeed = value;
			soundManager().setSpeed(mSoundName, value);
		}

		/**
		* Set the minimum distance a sound can be heard from.
		* @param value The new speed value.
		*/
		inline void setMinDistance(float value) {
			mMinDistance = value;
		}

		/**
		* Set the minimum distance a sound can be heard from.
		* @param value The new speed value.
		*/
		inline void setMaxDistance(float value) {
			mMaxDistance = value;
		}

		/**
		* Set the path of the audio
		* @param path The path to the audio file to play.
		* @param name The name to the audio file to play.
		*/
		inline void setSourcePath(std::string path) {
			
			mSoundPath = path.c_str();
		}

		/**
		* Set the name of the audio
		* @param path The path to the audio file to play.
		* @param name The name to the audio file to play.
		*/
		inline void setSourceName(std::string name) {
			mSoundName = name;
		}

		/**
		* Set the name of the group channel this audio is located in.
		* @param name The name of the group channel.
		*/
		inline void setGroupChannelName(std::string name) {
			mSoundGroup = name.c_str();
		}

		/**
		* Set if the audio will play in a loop
		*/
		inline void setLoop(bool loop) {
			mLoop = loop;
		}

		/**
		* Set if the audio will be a 3D audio
		*/
		inline void setIs3D(bool is3D) {
			mIs3D = is3D;
		}

		/**
		* Set if the adio will play at the start
		*/
		inline void setPlayOnStart(bool playOnStart) {
			mPlayOnStart = playOnStart;
		}

		/**
		* Get the volume of the audio.
		* @return The current volume value.
		*/
		inline float getVolume() {
			return mVolume;
		}


	private:
		float mVolume;  // The volume of the audio
		float mSpeed; // The speed of the audio
		float mMinDistance; //Minimum distance a 3D sound can be heard from.
		float mMaxDistance; //Maximun distance a 3D sound can be heard from.

		//FMOD::Sound* mSound; // The FMOD sound object
		int mSoundChannel; // The number of the channel this sound will be played on.
		const char* mSoundGroup; // The name of the channel group this sound will be played on.
		const char* mSoundPath; // The path to the audio file to play
		std::string mSoundName; // The name we give to the audio file to play
		bool mPlaying; // Whether the audio is currently playing or not
		bool mLoop; // Whether the audio should loop or not
		bool mIs3D;
		bool mPlayOnStart;


		Transform* mTransform = nullptr;
	};
}


#endif

