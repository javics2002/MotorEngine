#pragma once
#ifndef __ENTITYCOMPONENT_AUDIOSOURCE
#define __ENTITYCOMPONENT_AUDIOSOURCE

#include <string>

#include "EntityComponent/Component.h"
#include "EntityComponent/FactoryComponent.h"

namespace FMOD {
	class Sound;
}

namespace me {
	class SoundManager;
	class Transform;

	//Creates and destroys AudioSource components
	class FactoryAudioSource : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};


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

		void start() override;

		void update(const double& dt) override;

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
		void setVolume(float value);

		/**
		* Set the speed of the audio.
		* @param value The new speed value.
		*/
		void setSpeed(float value);

		/**
		* Set the minimum distance a sound can be heard from.
		* @param value The new speed value.
		*/
		void setMinDistance(float value);

		/**
		* Set the minimum distance a sound can be heard from.
		* @param value The new speed value.
		*/
		void setMaxDistance(float value);

		/**
		* Set the path of the audio
		* @param path The path to the audio file to play.
		*/
		void setSourcePath(std::string path);

		/**
		* Set the name of the audio
		* @param name The name to the audio file to play.
		*/
		void setSourceName(std::string name);

		/**
		* Set the name of the group channel this audio is located in.
		* @param name The name of the group channel.
		*/
		void setGroupChannelName(std::string name);

		/**
		* Set if the audio will play in a loop
		* @param loop True if the sound should be looping, false otherwise
		*/
		void setLoop(bool loop);

		/**
		* Set if the audio will be a 3D audio
		* @param threeD if we need 3d sound
		*/
		void setIsThreeD(bool threeD);

		/**
		* Set if the adio will play at the start
		* @param playOnStart True if the sound should starting played, false otherwise
		*/
		void setPlayOnStart(bool playOnStart);

		/**
		* Get the volume of the audio.
		* @return The current volume value.
		*/
		float getVolume();


	private:
		float mVolume;  // The volume of the audio
		float mSpeed; // The speed of the audio
		float mMinDistance; //Minimum distance a 3D sound can be heard from.
		float mMaxDistance; //Maximun distance a 3D sound can be heard from.

		//FMOD::Sound* mSound; // The FMOD sound object
		int mSoundChannel; // The number of the channel this sound will be played on.
		std::string mSoundGroup; // The name of the channel group this sound will be played on.
		std::string mSoundPath; // The path to the audio file to play
		std::string mSoundName; // The name we give to the audio file to play
		bool mPlaying; // Whether the audio is currently playing or not
		bool mLoop; // Whether the audio should loop or not
		bool mIsThreeD;
		bool mPlayOnStart;


		Transform* mTransform = nullptr;
	};
}


#endif

