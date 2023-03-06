#pragma once

#ifndef __EC_AUDIO_SOURCE
#define __EC_AUDIO_SOURCE

// Include necessary header files
#include "Component.h"
#include "Entity.h"

#include <Audio/SoundManager.h>

namespace me {
	class AudioSource : public Component
	{
	public:

		/**
		* Constructor for AudioSource class.
		* @param source The audio file to play.
		* @param volume The volume of the audio.
		* @param playOnStart Whether the audio should start playing on object start.
		* @param is3D Whether the audio should be treated as a 3D sound or not.
		* @param loop Whether the audio should loop or not.
		*/
		AudioSource(const char*,float volume,bool playOnStart,bool is3D,bool loop);
		~AudioSource();

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
		FMOD::Sound* mSound; // The FMOD sound object
		const char* mSource; // The audio file to play
		bool mPlaying; // Whether the audio is currently playing or not
		bool mLoop; // Whether the audio should loop or not
		bool mIs3D;

	};
}


#endif

