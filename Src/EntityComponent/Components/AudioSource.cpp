#include "AudioSource.h"
#include "Audio/SoundManager.h"
#include "Transform.h"
#include "EntityComponent/Entity.h"

me::AudioSource::AudioSource()
{
}

me::AudioSource::~AudioSource()
{
    //soundManager().deleteSound(mSound);
}

void me::AudioSource::start()
{
    // Create a 3D sound or a normal sound
    if (mIs3D)
        // sm().create3DSound(source, mSound, 1);
    // else sm().createNormalSound(source, mSound, 1);

    // If the sound was not created, output an error message
        if (!mSound)
            std::cout << "ERROR: Sound is null\n";

    if (mPlayOnStart)
        play();
}

void me::AudioSource::update()
{
    if (mIs3D) {
        //soundManager().setSoundPosition(mSound, mEntity->getComponent<me::Transform>("transform")->getPosition());
    }
}

void me::AudioSource::play()
{
    // sm().playSound(mSound, mLoop, 0,10);
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
