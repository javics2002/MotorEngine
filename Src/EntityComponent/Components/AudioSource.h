#pragma once
#ifndef __ENTITYCOMPONENT_AUDIOSOURCE
#define __ENTITYCOMPONENT_AUDIOSOURCE

#include <string>

#include "Component.h"

namespace FMOD {
	class Sound;
}

namespace me {
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
		}

		/**
		* Set the source of the audio
		* @param source The audio file to play.
		*/
		inline void setSource(std::string source) {
			mSource = source;
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
		FMOD::Sound* mSound; // The FMOD sound object
		std::string mSource; // The audio file to play
		bool mPlaying; // Whether the audio is currently playing or not
		bool mLoop; // Whether the audio should loop or not
		bool mIs3D;
		bool mPlayOnStart;

	};
}


#endif

