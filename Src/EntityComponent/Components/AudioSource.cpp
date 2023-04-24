#include "AudioSource.h"
//#include "Audio/SoundManager.h"
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
    bool error;
    // Create a 3D sound or a normal sound
    if (mIs3D)
         error = soundManager().create3DSound(mSoundPath, mSoundName, mMinDistance, mMaxDistance);
     else error = soundManager().createNormalSound(mSoundPath, mSoundName);



    // If the sound was not created, output an error message
        if (!error)
            std::cout << "ERROR: Sound is null\n";

    if (mPlayOnStart)
        play();
}

void me::AudioSource::update()
{
    if (mIs3D) {
        soundManager().setSoundPosition(mSoundName, mEntity->getComponent<me::Transform>("transform")->getPosition());
    }
}

void me::AudioSource::play()
{
    //soundManager().playSound(mSoundName, mLoop,);
}

void me::AudioSource::stop()
{
    //sm().pauseSound(mSound, true);
}

void me::AudioSource::pause()
{
    //soundManager().pauseSound(mSound, true);
}

void me::AudioSource::resume()
{
    //soundManager().pauseSound(mSound, false);
}

bool me::AudioSource::isPlaying()
{
    return mPlaying;
}
