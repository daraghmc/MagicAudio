#ifndef MADXSOUNDINFO_H
#define MADXSOUNDINFO_H

#include <dsound.h>

namespace MagicAudio
{

class DxAudioStream;

class SoundInfo
{
public:
    SoundInfo();
    ~SoundInfo();

    IDirectSoundBuffer8* m_pqBuffer;
    IDirectSound3DBuffer8* m_pq3DBuffer;
    DxAudioStream* m_pkStream;
};

} // namespace MagicAUdio

#endif // MADXSOUNDINFO_H 
