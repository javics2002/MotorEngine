#include "SoundManager.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>

me::SoundManager::SoundManager() {

	mResult = FMOD::System_Create(&mSoundSystem);      // Create the main system object.
	checkFMODResult(mResult);

	mResult = mSoundSystem->init(MAX_CHANNELS, FMOD_INIT_3D_RIGHTHANDED, 0);    // Initialize FMOD.
	checkFMODResult(mResult);
	mResult = mSoundSystem->set3DSettings(0.0f, DISTANCE_FACTOR, ROLLOFF_SCALE);
	checkFMODResult(mResult);

	mSoundSystem->createChannelGroup("master", &mMaster);
	mChannelGroupMaps["master"] = mMaster;
	mSoundSystem->createChannelGroup("effects", &mEffects);
	mChannelGroupMaps["effects"] = mEffects;
	mSoundSystem->createChannelGroup("music", &mMusic);
	mChannelGroupMaps["music"] = mMusic;

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
#ifdef _DEBUG
		exit(-1);
#endif // DEBUG
		return false;
	}
	return true;
}

FMOD::Sound* me::SoundManager::getSound(std::string soundName)
{
	nameToLower(soundName);
	auto returnedSound= mSoundsMap.find(soundName);
	if (returnedSound == mSoundsMap.end()) return nullptr;
	return returnedSound->second;
}

FMOD::Channel* me::SoundManager::getChannel(std::string soundName)
{
	nameToLower(soundName);
	FMOD::Sound* soundHandle = getSound(soundName);
	if (soundHandle != nullptr) {
		auto returnedChannel = mLastPlayedMap.find(soundHandle);
		if (returnedChannel == mLastPlayedMap.end()) return nullptr;
		return mChannelsVector[returnedChannel->second];
	}
	else {
		return nullptr;
	}
}

FMOD::ChannelGroup* me::SoundManager::getGroupChannel(std::string channelGroupName)
{
	nameToLower(channelGroupName);
	auto returnedGroup = mChannelGroupMaps.find(channelGroupName);
	if (returnedGroup == mChannelGroupMaps.end()) return nullptr;
	return returnedGroup->second;
}

bool me::SoundManager::changeChannelVolume(std::string channelGroupName, float volume)
{
	nameToLower(channelGroupName);
	auto returnedGroup = mChannelGroupMaps.find(channelGroupName);
	if (returnedGroup == mChannelGroupMaps.end()) return false;
	mResult = returnedGroup->second->setVolume(volume);
	return checkFMODResult(mResult);
}

void me::SoundManager::nameToLower(std::string& name)
{
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace),
		name.end());
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
}

me::SoundManager::~SoundManager()
{
	for (auto s : mSoundsMap)
	{
		mResult = s.second->release();
		checkFMODResult(mResult);
	}
	mSoundsMap.clear();

	mResult = mSoundSystem->release();
	checkFMODResult(mResult);
}

void me::SoundManager::systemRefresh(const double& dt)
{
	mResult = mSoundSystem->update();
	checkFMODResult(mResult);
}

bool me::SoundManager::create3DSound(std::string soundPath, std::string soundName, float minDistance, float maxDistance, bool loop)
{
	soundPath = "Assets/Sounds/" + soundPath;
	nameToLower(soundName);
	FMOD::Sound* newSoundHandle;
	auto soundHandle = getSound(soundName);
	if (soundHandle != nullptr) return false;

	if (loop) {
		mResult = mSoundSystem->createSound(soundPath.c_str(), FMOD_3D_LINEARROLLOFF | FMOD_3D | FMOD_LOOP_NORMAL, 0, &newSoundHandle);
	}
	else {
		mResult = mSoundSystem->createSound(soundPath.c_str(), FMOD_3D_LINEARROLLOFF | FMOD_3D, 0, &newSoundHandle);
	}
	
	if(!checkFMODResult(mResult)) return false;

	mResult = newSoundHandle->set3DMinMaxDistance(minDistance, maxDistance);
	if (!checkFMODResult(mResult)) return false;

	if (checkFMODResult(mResult)) {
		std::pair<std::string, FMOD::Sound*> newSound(soundName, newSoundHandle);
		mSoundsMap.insert(newSound);
#ifdef _DEBUG
		std::cout << "Sound created." << "\n";
#endif // DEBUG
		return true;
	} 
	else {
		return false;
	}
	
	
}

bool me::SoundManager::createNormalSound(std::string soundPath, std::string soundName, bool loop)
{
	soundPath = "Assets/Sounds/" + soundPath;
	nameToLower(soundName);
	FMOD::Sound* newSoundHandle;
	auto soundHandle = getSound(soundName);
	if (soundHandle != nullptr) return false;
	
	if (loop) {
		mResult = mSoundSystem->createSound(soundPath.c_str(), FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &newSoundHandle);
	}
	else {
		mResult = mSoundSystem->createSound(soundPath.c_str(), FMOD_DEFAULT, 0, &newSoundHandle);
	}

	if(checkFMODResult(mResult)){
		std::pair<std::string, FMOD::Sound*> newSound(soundName, newSoundHandle);
		mSoundsMap.insert(newSound);
#ifdef _DEBUG
		std::cout << "Sound created." << "\n";
#endif // DEBUG
		return true;
	}
	else {
		return false;
	}
}

bool me::SoundManager::pauseSound(std::string soundName, bool pause)
{
	nameToLower(soundName);
	bool isPaused;
	FMOD::Channel* channel = getChannel(soundName);
	if (channel != nullptr) {
		mResult = channel->getPaused(&isPaused);
		checkFMODResult(mResult);
		channel->setPaused(pause);
		return true;
	}
	else {
		return false;
	}
}

bool me::SoundManager::stopSound(std::string soundName)
{
	nameToLower(soundName);
	bool isPaused;
	FMOD::Channel* channel = getChannel(soundName);
	if (channel != nullptr) {
		mResult = channel->getPaused(&isPaused);
		checkFMODResult(mResult);
		channel->stop();
		return true;
	}
	else {
		return false;
	}
}

bool me::SoundManager::stopEverySound()
{
	for (auto i : mChannelsVector) {
		i->stop();
	}
	return true;
}

bool me::SoundManager::playSound(std::string soundName, std::string channelGroup, Vector3* channelPos, Vector3* channelVel)
{
	nameToLower(soundName);
	FMOD::Sound* soundHandle = getSound(soundName);
	if (soundHandle == nullptr) return false;

	/*FMOD_MODE oldSoundMode;
	soundHandle->getMode(&oldSoundMode);*/

	//if (isLoop) {
	//	setMode(soundName, FMOD_LOOP_NORMAL);
	//	//soundHandle->setMode(FMOD_LOOP_NORMAL);
	//	/*if (timesLooped > 0)
	//	soundHandle->setLoopCount(timesLooped);*/

	//}
	//else {
	//	//setMode(soundName, FMOD_LOOP_OFF);
	//}

	for (int i = 0; i < mChannelsVector.size(); i++) {
		bool isPlaying;
		mChannelsVector[i]->isPlaying(&isPlaying);

		if (isPlaying) continue;

		/*FMOD_MODE newSoundMode;
		soundHandle->getMode(&newSoundMode);
		soundHandle->setMode(newSoundMode | oldSoundMode);*/

		FMOD_MODE finalSoundMode;
		soundHandle->getMode(&finalSoundMode);

		auto playedChannelGroup = getGroupChannel(channelGroup);
		if (playedChannelGroup == nullptr) return false;
		mResult = mSoundSystem->playSound(soundHandle, playedChannelGroup, false, &mChannelsVector[i]);
		checkFMODResult(mResult);

		if (finalSoundMode & FMOD_3D) {
			FMOD_VECTOR v = channelVel->v3ToFmodV3(), p = channelPos->v3ToFmodV3();
			mChannelsVector[i]->set3DAttributes(&p, &v);
		}

		mLastPlayedMap[soundHandle] = i;

		break;
	}
	return true;
}

bool me::SoundManager::deleteSound(std::string soundName)
{
	nameToLower(soundName);
	FMOD::Sound* soundHandle = getSound(soundName);
	if (soundHandle == nullptr) return false;

	//mResult = soundHandle->release();

	mLastPlayedMap.erase(soundHandle);

	return checkFMODResult(mResult);
}

void me::SoundManager::updateListenersPosition(int index, Vector3 listenerPos, Vector3 listenerFW, Vector3 listenerUP, Vector3 listenerVel)
{
	FMOD_VECTOR pos = listenerPos.v3ToFmodV3(), fw = listenerFW.v3ToFmodV3(), up = listenerUP.v3ToFmodV3(), vel = listenerVel.v3ToFmodV3();
	mSoundSystem->set3DListenerAttributes(index, &pos, &vel, &fw, &up);
}

void me::SoundManager::removeListener(int index)
{
	mListeners[index] = false;
	updateListenersPosition(index, { 999999,999999,999999 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 });
}

bool me::SoundManager::setSoundAtributes(std::string soundName, Vector3 position, Vector3 velocity)
{
	nameToLower(soundName);
	FMOD::Channel* channelHandle = getChannel(soundName);
	if (channelHandle == nullptr) return false;
	FMOD_VECTOR p = position.v3ToFmodV3(), v = velocity.v3ToFmodV3();

	channelHandle->set3DAttributes(&p, &v);
	return true;
}

bool me::SoundManager::setPitchVelocity(std::string soundName, Vector3 velocity)
{
	nameToLower(soundName);
	FMOD::Channel* channel = getChannel(soundName);
	float velMagnitude = velocity.magnitude();
	float newPitch = 1 + (velMagnitude - 1) / 10;
	if (channel != nullptr) {
		channel->setPitch(newPitch);
		return true;
	}
	else return false;
}

bool me::SoundManager::setSpeed(std::string soundName, float newSpeed)
{
	nameToLower(soundName);
	FMOD::Sound* soundHandle = getSound(soundName);
	if (soundHandle == nullptr) return false;

	mResult = soundHandle->setMusicSpeed(newSpeed);

	return checkFMODResult(mResult);
}

bool me::SoundManager::setMode(std::string soundName, FMOD_MODE newMode)
{
	nameToLower(soundName);
	FMOD::Sound* soundHandle = getSound(soundName);
	if (soundHandle == nullptr) return false;
	FMOD_MODE soundMode;
	soundHandle->getMode(&soundMode);
	FMOD_MODE newSoundMode;
	newSoundMode = soundMode | newMode;
	mResult = soundHandle->setMode(newSoundMode);
	soundHandle->getMode(&soundMode);

	if (soundMode & FMOD_3D)
	{
		std::cout << "3d" << " ";
	}
	if (soundMode & FMOD_3D_LINEARROLLOFF)
	{
		std::cout << "atenuacion" << " ";
	}
	if (soundMode & FMOD_LOOP_NORMAL)
	{
		std::cout << "loop" << " ";
	}

	checkFMODResult(mResult);
}

bool me::SoundManager::setMinMaxDistance(std::string soundName,float minDistance, float maxDistance)
{
	nameToLower(soundName);
	auto soundHandle = getSound(soundName);
	if (soundHandle == nullptr) return false;
	soundHandle->set3DMinMaxDistance(minDistance, maxDistance);
	return true;
}

bool me::SoundManager::createChannelGroup(std::string groupName)
{
	nameToLower(groupName);
	const char* channelGroupName = groupName.c_str();
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

bool me::SoundManager::setChannelVolume(std::string groupName, float newVolume)
{
	nameToLower(groupName);
	const char* channelGroup = groupName.c_str();
	FMOD::ChannelGroup* changedGroup = getGroupChannel(channelGroup);
	if (changedGroup == nullptr) {
		return false;
	}
	else {
		return changeChannelVolume(channelGroup, newVolume);
	}
}

bool me::SoundManager::setVolume(std::string soundName, float newVolume)
{
	nameToLower(soundName);
	FMOD::Channel* channel = getChannel(soundName);
	if (channel != nullptr) {
		mResult = channel->setVolume(newVolume);
		return checkFMODResult(mResult);
	}
	else {
		return false;
	}
}

float me::SoundManager::getVolume(std::string soundName)
{
	nameToLower(soundName);
	FMOD::Channel* channel = getChannel(soundName);
	float volume;
	if (channel != nullptr) {
		mResult = channel->getVolume(&volume);
		checkFMODResult(mResult);
		return volume;
	}
}