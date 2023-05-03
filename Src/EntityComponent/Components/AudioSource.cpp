#include "AudioSource.h"
#include "Audio/SoundManager.h"
#include "Transform.h"
#include "EntityComponent/Entity.h"

me::AudioSource::AudioSource()
{
}

me::AudioSource::~AudioSource()
{
    soundManager().deleteSound(mSoundName);
}

void me::AudioSource::start()
{
    mTransform = mEntity->getComponent<Transform>("transform");
    bool error;
    // Create a 3D sound or a normal sound
    if (mIsThreeD)
         error = soundManager().create3DSound(mSoundPath, mSoundName, mMinDistance, mMaxDistance, mLoop);
     else error = soundManager().createNormalSound(mSoundPath, mSoundName, mLoop);

    // If the sound was not created, output an error message
        if (!error)
            std::cout << "ERROR: Sound was not created or already existed.\n";

    if (mPlayOnStart)
        play();
}

void me::AudioSource::update(const double& dt)
{
    if (mIsThreeD) {
        soundManager().setSoundAtributes(mSoundName, mEntity->getComponent<me::Transform>("transform")->getPosition(), mEntity->getComponent<me::Transform>("transform")->getVelocity());
    }
}

void me::AudioSource::play()
{
    Vector3 pos = mTransform->getPosition();
    Vector3 vel = mTransform->getVelocity();
   soundManager().playSound(mSoundName, mSoundGroup, &pos, &vel);
   if (!firstPlayed) {
       soundManager().setVolume(mSoundName, mVolume);
       firstPlayed = true;
   }
    mPlaying = true;
}

void me::AudioSource::stop()
{
    soundManager().stopSound(mSoundName);
}

void me::AudioSource::pause()
{
    soundManager().pauseSound(mSoundName, true);
}

void me::AudioSource::resume()
{
    soundManager().pauseSound(mSoundName, false);
}

bool me::AudioSource::isPlaying()
{
    return mPlaying;
}

void me::AudioSource::setVolume(float value) {
    mVolume = value;
    //soundManager().setVolume(mSoundName, value);
}

void me::AudioSource::setSpeed(float value) {
    mSpeed = value;
    //soundManager().setSpeed(mSoundName, value);
}

void me::AudioSource::setMinDistance(float value) {
    mMinDistance = value * DISTANCE_FACTOR;
}

void me::AudioSource::setMaxDistance(float value) {
    mMaxDistance = value * DISTANCE_FACTOR;
}

void me::AudioSource::setSourcePath(std::string path) {
    mSoundPath = path;
}

void me::AudioSource::setSourceName(std::string name) {
    mSoundName = name;
}

void me::AudioSource::setGroupChannelName(std::string name) {
    mSoundGroup = name;
}

void me::AudioSource::setLoop(bool loop) {
    mLoop = loop;
}

void me::AudioSource::setIsThreeD(bool threeD) {
    mIsThreeD = threeD;
}

void me::AudioSource::setPlayOnStart(bool playOnStart) {
    mPlayOnStart = playOnStart;
}

float me::AudioSource::getVolume() {
    return mVolume;
}
