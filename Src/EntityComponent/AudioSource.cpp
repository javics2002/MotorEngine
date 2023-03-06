#include "AudioSource.h"
#include "Transform.h"

me::AudioSource::AudioSource(const char* source, float volume, bool playOnStart, bool is3D, bool loop)
{
    mSource = source;
    mVolume = volume;
    mLoop = loop;
    mIs3D = is3D;

    // Create a 3D sound or a normal sound
    if (is3D)
        sm().create3DSound(source, mSound, 1);
    else sm().createNormalSound(source, mSound, 1);

    // If the sound was not created, output an error message
    if (!mSound) 
        std::cout << "ERROR: Sound is null\n";

    setVolume(volume);
    if (playOnStart)
        play();
}

me::AudioSource::~AudioSource()
{
    sm().deleteSound(mSound);
}

void me::AudioSource::update()
{
    if (mIs3D) {
        sm().setSoundPosition(mSound, mEntity->getComponent<me::Transform>("transform")->getPosition());
    }
}

void me::AudioSource::play()
{
    sm().playSound(mSound, mLoop, 0,10);
}

void me::AudioSource::stop()
{
    sm().stopSound(mSound);
}

void me::AudioSource::pause()
{
    sm().pauseSound(mSound, true);
}

void me::AudioSource::resume()
{
    sm().pauseSound(mSound, false);
}

bool me::AudioSource::isPlaying()
{
    return mPlaying;
}
