#ifndef _MAAUDIORENDERER_H
#define _MAAUDIORENDERER_H

#include "MASound1D.h"
#include "MASound2D.h"
#include "MASound3D.h"
#include "MASequence.h"

namespace MagicAudio
{

///////////////////////////////////////////////////////////////////////////////

class AudioFormat
{
public:
    int iSampleRate;
    int iBytesPerSample;
    int iChannels;
    bool b3D;
};

///////////////////////////////////////////////////////////////////////////////

class AudioRenderer
{
public:
    // General methods
    virtual void Initialize (int iWindowID, AudioFormat* pkFormat = NULL) = 0;
    virtual void SetPath (wchar_t* acPath) = 0;
    virtual void ScanPath () = 0;
    virtual void Unload (Audio* pkAudio) = 0;
    virtual void Play (Audio* pkAudio) = 0;
    virtual bool IsPlaying (Audio* pkAudio) = 0;
    virtual void Stop (Audio *pkAudio) = 0;
    virtual void Pause (Audio* pkAudio) = 0;
    virtual void SetLoop (Audio* pkAudio) = 0;
    virtual void SetVolume (Audio* pkAudio) = 0;
    virtual bool UpdateEffects (Audio* pkAudio, 
    AudioEffect::TYPE eType = AudioEffect::NONE) = 0;
    virtual ~AudioRenderer () {};
};

///////////////////////////////////////////////////////////////////////////////

class SoundRenderer : public AudioRenderer
{
public:
    // 1D sound source methods
    virtual void Load (Sound1D* pkSound) = 0;

    // 2D sound source methods
    virtual void Load (Sound2D* pkSound) = 0;
 
    virtual void SetPan (Panable* pkSound) = 0;

    // 3D sound source methods
    virtual void Load (Sound3D* pkSound) = 0;
    virtual void SetAll (Sound3D* pkSound, bool bDefer = false) = 0;
    virtual void SetConeAngles (Sound3D* pkSound, bool bDefer = false) = 0;
    virtual void SetMode (Sound3D* pkSound, bool bDefer = false) = 0;
    virtual void SetOrientation (Sound3D* pkSound, bool bDefer = false) = 0;
    virtual void SetOutsideVolume (Sound3D* pkSound, bool bDefer = false) = 0;
    virtual void SetPosition (Sound3D* pkAudio3D, bool bDefer = false) = 0;
    virtual void SetVelocity (Sound3D* pkSound, bool bDefer = false) = 0;
    virtual void SetVolumeDistances (Sound3D* pkSound, bool bDefer = false) = 0;

    // 3D listener methods
    virtual void SetAll (Listener3D* pkListener, bool bDefer = false) = 0;
    virtual void SetDoppler (Listener3D* pkListener, bool bDefer = false) = 0;
    virtual void SetOrientation (Listener3D* pkListener, bool bDefer = false) = 0;
    virtual void SetPosition (Listener3D* pkListener, bool bDefer = false) = 0;
    virtual void SetRolloff (Listener3D* pkListener, bool bDefer = false) = 0;
    virtual void SetVelocity (Listener3D* pkListener, bool bDefer = false) = 0;
    virtual void SetDistanceScale (Listener3D* pkListener, bool bDefer = false) = 0;
    virtual void CommitDeferredSettings () = 0;

    virtual ~SoundRenderer() {};
};

} // namespace MagicAudio

#endif // _MAAUDIORENDERER_H