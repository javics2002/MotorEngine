#include "SoundManager.h"

me::SoundManager::SoundManager() {

	result = FMOD::System_Create(&Sound_System);      // Create the main system object.
	checkFMODResult(result);

	result = Sound_System->init(MAX_CHANNELS, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	checkFMODResult(result);

	Sound_System->createChannelGroup("master", &master);
	Sound_System->createChannelGroup("effects", &effects);
	Sound_System->createChannelGroup("music", &music);

	master->addGroup(effects);
	master->addGroup(music);

	mListeners = std::vector<bool>(FMOD_MAX_LISTENERS, false); // Vector used to know which listeners are being used

	channelsVector.reserve(MAX_CHANNELS);
	for (int i = 0; i < MAX_CHANNELS; i++) {
		channelsVector.push_back(nullptr);
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
	//TO BE IMPLEMENTED
	return nullptr;
}

void me::SoundManager::systemRefresh()
{
	result = Sound_System->update();
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void me::SoundManager::create3DSound(const char* soundPath, FMOD::Sound*& soundHandle, int channel)
{
	//TO BE IMPLEMENTED
}

void me::SoundManager::createNormalSound(const char* soundPath, FMOD::Sound*& soundHandle, int channel)
{
	result = Sound_System->createSound("Assets/Sounds/wave.mp3", FMOD_DEFAULT, 0, &soundHandle);
	if(checkFMODResult(result)){
		std::pair<FMOD::Sound*, int> newSound(soundHandle, channel);
		lastPlayedMap.insert(newSound);
	}
}

void me::SoundManager::stopSound(FMOD::Sound* sound)
{
	//TO BE IMPLEMENTED
}

void me::SoundManager::pauseSound(FMOD::Sound* sound, bool pause)
{
	//TO BE IMPLEMENTED
}

//void me::SoundManager::playSound(FMOD::Sound* soundHandle, bool isLoop, int channelGroup, int timesLooped)
void me::SoundManager::playSound(FMOD::Sound* soundHandle, bool isLoop, const char* channelGroup, int timesLooped)
{
	if (isLoop) {
		result = soundHandle->setMode(FMOD_LOOP_NORMAL);
		checkFMODResult(result);
		if (timesLooped < -1) timesLooped = -1;
		soundHandle->setLoopCount(timesLooped);
	}
	else {
		result = soundHandle->setMode(FMOD_LOOP_OFF);
		checkFMODResult(result);
	}

	for (int i = 0; i < channelsVector.size(); i++) {
		bool isPlaying;
		channelsVector[i]->isPlaying(&isPlaying);

		if (isPlaying) continue;

		auto playedChannelGroup = channelGroupMaps.find(channelGroup);
		if (playedChannelGroup == channelGroupMaps.end()) {
			createChannel(channelGroup);
		}

		
		result = Sound_System->playSound(soundHandle, playedChannelGroup->second, false, &channelsVector[i]);
		checkFMODResult(result);
	

		lastPlayedMap.find(soundHandle)->second = i;

		break;
	}
}

void me::SoundManager::deleteSound(FMOD::Sound* soundHandle)
{
	result = soundHandle->release();
	checkFMODResult(result);

	lastPlayedMap.erase(soundHandle);
}

void me::SoundManager::updateListenersPosition(int index, FMOD_VECTOR listenerPos, FMOD_VECTOR listenerFW, FMOD_VECTOR listenerUP, FMOD_VECTOR listenerVel)
{
	Sound_System->set3DListenerAttributes(index, &listenerPos, &listenerVel, &listenerFW, &listenerUP);
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
	result = soundHandle->setMusicSpeed(newSpeed);
	checkFMODResult(result);
}

void me::SoundManager::setMode(FMOD::Sound* sound, int flags)
{
	//TO BE IMPLEMENTED
}
void me::SoundManager::createChannel(const char* channelGroupName)
{
	FMOD::ChannelGroup* newChannelGroup;
	Sound_System->createChannelGroup(channelGroupName, &newChannelGroup);
	std::pair<std::string, FMOD::ChannelGroup*> newGroup(channelGroupName, newChannelGroup);
}
