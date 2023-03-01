#include "SoundManager.h"

me::SoundManager::SoundManager() {

	result = FMOD::System_Create(&Sound_System);      // Create the main system object.
	checkFMODResult(result);

	result = Sound_System->init(MAX_CHANNELS, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	checkFMODResult(result);

	Sound_System->createChannelGroup("Master", &master);
	Sound_System->createChannelGroup("Effects", &effects);
	Sound_System->createChannelGroup("Music", &music);

	master->addGroup(effects);
	master->addGroup(music);

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

void me::SoundManager::create3DSound(const char* soundPath, FMOD::Sound* soundHandle, int channel)
{
}

void me::SoundManager::createNormalSound(const char* soundPath, FMOD::Sound* soundHandle, int channel)
{
	result = Sound_System->createSound("Assets/Sounds/wave.mp3", FMOD_DEFAULT, 0, &soundHandle);
	if(checkFMODResult(result)){
		std::pair<FMOD::Sound*, int> newSound(soundHandle, channel);
		lastPlayedMap.insert(newSound);
	}
}

void me::SoundManager::playSound(FMOD::Sound* soundHandle, bool isLoop, int channelGroup, int timesLooped = -1)
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

		switch (channelGroup) {
		case EFFECTS:
			result = Sound_System->playSound(soundHandle, effects, false, &channelsVector[i]);
			checkFMODResult(result);
			break;
		case MUSIC:
			result = Sound_System->playSound(soundHandle, music, false, &channelsVector[i]);
			checkFMODResult(result);
			break;
		default:
			break;
		}

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

void me::SoundManager::setSpeed(FMOD::Sound* soundHandle, float newSpeed)
{
	result = soundHandle->setMusicSpeed(newSpeed);
	checkFMODResult(result);
}
