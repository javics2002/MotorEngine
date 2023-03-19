#include "SoundManager.h"

#include <fmod.hpp>
#include <fmod_errors.h>
#include <Utils/Vector3.h>

me::SoundManager::SoundManager() {

	mResult = FMOD::System_Create(&mSoundSystem);      // Create the main system object.
	checkFMODResult(mResult);

	mResult = mSoundSystem->init(MAX_CHANNELS, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	checkFMODResult(mResult);
	mResult = mSoundSystem->set3DSettings(DOPPLER_SCALE, DISTANCE_FACTOR, ROLLOFF_SCALE);
	checkFMODResult(mResult);

	mSoundSystem->createChannelGroup("master", &mMaster);
	mSoundSystem->createChannelGroup("effects", &mEffects);
	mSoundSystem->createChannelGroup("music", &mMusic);

	mMaster->addGroup(mEffects);
	mMaster->addGroup(mMusic);

	mListeners = std::vector<bool>(FMOD_MAX_LISTENERS, false); // Vector used to know which listeners are being used

	mChannelsVector.reserve(MAX_CHANNELS);
	for (int i = 0; i < MAX_CHANNELS; i++) {
		mChannelsVector.push_back(nullptr);
	}
}

bool me::SoundManager::checkFMODResult(FMOD_RESULT FMODResult)
{
	if (FMODResult != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", FMODResult, FMOD_ErrorString(FMODResult));
#ifdef DEBUG
		exit(-1);
#endif // DEBUG
	}
	return true;
}

FMOD::Channel* me::SoundManager::getChannel(FMOD::Sound* sound)
{
	auto returnedChannel = mLastPlayedMap.find(sound);
	if (returnedChannel == mLastPlayedMap.end()) return nullptr;
	return mChannelsVector[returnedChannel->second];
}

FMOD::ChannelGroup* me::SoundManager::getGroupChannel(std::string groupName)
{
	auto returnedGroup = mChannelGroupMaps.find(groupName);
	if (returnedGroup == mChannelGroupMaps.end()) return nullptr;
	return returnedGroup->second;
}

void me::SoundManager::changeChannelVolume(FMOD::ChannelGroup* group, float volume)
{
	mResult = group->setVolume(volume);
	checkFMODResult(mResult);
}

void me::SoundManager::systemRefresh()
{
	mResult = mSoundSystem->update();
	if (mResult != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", mResult, FMOD_ErrorString(mResult));
		exit(-1);
	}
}

void me::SoundManager::create3DSound(const char* soundPath, FMOD::Sound*& soundHandle, int channel, float minDistance, float maxDistance)
{
	mResult = mSoundSystem->createSound("Assets/Sounds/wave.mp3", FMOD_3D, 0, &soundHandle);

	if (checkFMODResult(mResult)) {
		std::pair<FMOD::Sound*, int> newSound(soundHandle, channel);
		mLastPlayedMap.insert(newSound);
	}
	mResult = soundHandle->set3DMinMaxDistance(minDistance * DISTANCE_FACTOR, maxDistance * DISTANCE_FACTOR);
	checkFMODResult(mResult);
}

void me::SoundManager::createNormalSound(const char* soundPath, FMOD::Sound*& soundHandle, int channel)
{
	mResult = mSoundSystem->createSound("Assets/Sounds/wave.mp3", FMOD_DEFAULT, 0, &soundHandle);
	if(checkFMODResult(mResult)){
		std::pair<FMOD::Sound*, int> newSound(soundHandle, channel);
		mLastPlayedMap.insert(newSound);
	}
}

void me::SoundManager::pauseSound(FMOD::Sound* sound, bool pause)
{
	bool isPaused;
	auto channel = getChannel(sound);
	if (channel != nullptr){
		mResult = channel->getPaused(&isPaused);
		checkFMODResult(mResult);
		channel->setPaused(pause);
	}
}

bool me::SoundManager::playSound(FMOD::Sound* soundHandle, bool isLoop, const char* channelGroup, FMOD_VECTOR* channelPos, FMOD_VECTOR* channelVel, int timesLooped)
{
	if (isLoop) {
		mResult = soundHandle->setMode(FMOD_LOOP_NORMAL);
		checkFMODResult(mResult);
		if (timesLooped < -1) timesLooped = -1;
		soundHandle->setLoopCount(timesLooped);
	}
	else {
		mResult = soundHandle->setMode(FMOD_LOOP_OFF);
		checkFMODResult(mResult);
	}

	for (int i = 0; i < mChannelsVector.size(); i++) {
		bool isPlaying;
		mChannelsVector[i]->isPlaying(&isPlaying);

		if (isPlaying) continue;

		FMOD_MODE soundMode;
		soundHandle->getMode(&soundMode);
		if (soundMode == FMOD_3D) {
			mChannelsVector[i]->set3DAttributes(channelPos, channelVel);
		}

		auto playedChannelGroup = getGroupChannel(channelGroup);
		if (playedChannelGroup == nullptr) return false;

		
		mResult = mSoundSystem->playSound(soundHandle, playedChannelGroup, false, &mChannelsVector[i]);
		checkFMODResult(mResult);
	

		mLastPlayedMap.find(soundHandle)->second = i;

		break;
	}
	return true;
}

void me::SoundManager::deleteSound(FMOD::Sound* soundHandle)
{
	mResult = soundHandle->release();
	checkFMODResult(mResult);

	mLastPlayedMap.erase(soundHandle);
}

void me::SoundManager::updateListenersPosition(int index, Vector3 listenerPos, Vector3 listenerFW, Vector3 listenerUP, Vector3 listenerVel)
{
	//mSoundSystem->set3DListenerAttributes(index, &lPos, &listenerVel, &listenerFW, &listenerUP);
}

void me::SoundManager::removeListener(int index)
{
	mListeners[index] = false;
	updateListenersPosition(index, { 999999,999999,999999 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 });
}

void me::SoundManager::setSoundPosition(FMOD::Sound*& sound, Vector3 position)
{
	//TO BE IMPLEMENTED
}

void me::SoundManager::setSpeed(FMOD::Sound* soundHandle, float newSpeed)
{
	mResult = soundHandle->setMusicSpeed(newSpeed);
	checkFMODResult(mResult);
}

void me::SoundManager::setMode(FMOD::Sound* sound, FMOD_MODE newMode)
{
	sound->setMode(newMode);
}
bool me::SoundManager::createChannelGroup(char* channelGroupName)
{
	if ((int(channelGroupName[0]) > 96) && (int(channelGroupName[0]) < 122)) channelGroupName[0] - 32;
	auto channelGroup = mChannelGroupMaps.find(channelGroupName);
	if (channelGroup == mChannelGroupMaps.end()) {
			FMOD::ChannelGroup* newChannelGroup;
	
			mSoundSystem->createChannelGroup(channelGroupName, &newChannelGroup);
			std::pair<std::string, FMOD::ChannelGroup*> newGroup(channelGroupName, newChannelGroup);
			mChannelGroupMaps.insert(newGroup);
			mMaster->addGroup(newChannelGroup);
			return true;
	}
	return false;
}

bool me::SoundManager::setChannelVolume(const char* channelGroup, float newVolume)
{
	auto changedGroup = getGroupChannel(channelGroup);
	if (changedGroup == nullptr) {
		return false;
	}
	else {
		changeChannelVolume(changedGroup, newVolume);
	}
}

void me::SoundManager::setVolume(FMOD::Sound* sound, float newVolume)
{
	auto channel = getChannel(sound);
	if (channel != nullptr) channel->setVolume(newVolume);
}

float me::SoundManager::getVolume(FMOD::Sound* sound)
{
	auto channel = getChannel(sound);
	float volume;
	if (channel != nullptr) {
		channel->getVolume(&volume);
		return volume;
	}
}