#ifndef MADXSOUNDRENDERER_H
#define MADXSOUNDRENDERER_H

#include "MADxSoundInfo.h"
#include "MADxAudioRenderer.h"
#include "MAAudioRenderer.h"

#include <map>

namespace MagicAudio
{

class DxSoundRenderer : public SoundRenderer, public DxAudioRenderer
{
public:
    DxSoundRenderer ();
    virtual ~DxSoundRenderer ();

    // General methods
    virtual void Initialize (int iWindowID, AudioFormat* pkFormat = NULL);
    virtual void SetPath (wchar_t* acPath);
    virtual void ScanPath ();
    virtual void Unload (Audio* pkAudio);
    virtual void Play (Audio* pkAudio);
    virtual bool IsPlaying (Audio* pkAudio);
    virtual void Stop (Audio* pkAudio);
    virtual void Pause (Audio* pkAudio);
    virtual void SetLoop (Audio* pkAudio);
    virtual void SetVolume (Audio* pkAudio);
    virtual void CommitDeferredSettings ();

    // 1D sound source methods
    virtual void Load (Sound1D* pkSound);

    // 2D sound source methods
    virtual void Load (Sound2D* pkSound);
    virtual void SetPan (Panable* pkSound);

    // 3D sound source methods
    virtual void Load (Sound3D* pkSound);
    virtual void SetAll (Sound3D* pkSound, bool bDefer = false);
    virtual void SetConeAngles (Sound3D* pkSound, bool bDefer = false);
    virtual void SetMode (Sound3D* pkSound, bool bDefer = false);
    virtual void SetOrientation (Sound3D* pkSound, bool bDefer = false);
    virtual void SetOutsideVolume (Sound3D* pkSound, bool bDefer = false);
    virtual void SetPosition (Sound3D* pkAudio3D, bool bDefer = false);
    virtual void SetVelocity (Sound3D* pkSound, bool bDefer = false);
    virtual void SetVolumeDistances (Sound3D* pkSound, bool bDefer = false);

    // 3D listener methods
    virtual void SetAll (Listener3D* pkListener, bool bDefer = false);
    virtual void SetDoppler (Listener3D* pkListener, bool bDefer = false);
    virtual void SetOrientation (Listener3D* pkListener, bool bDefer = false);
    virtual void SetPosition (Listener3D* pkListener, bool bDefer = false);
    virtual void SetRolloff (Listener3D* pkListener, bool bDefer = false);
    virtual void SetVelocity (Listener3D* pkListener, bool bDefer = false);
    virtual void SetDistanceScale (Listener3D* pkListener, bool bDefer = false);

    // Realtime effects methods
    virtual bool UpdateEffects (Audio* pkAudio, 
        AudioEffect::TYPE eType = AudioEffect::NONE);

protected:
    SoundInfo* FindSound (Audio* pkAudio);
    void Stop (IDirectSoundBuffer8* pqBuffer);
    bool IsPlaying (IDirectSoundBuffer8* pqBuffer);
    void SetPosition (Audio3D* pkAudio3D, bool bDefer = false);
    void Unload (SoundInfo* pkSegInfo);
    long ScaleVolume(int iVolume);
    long ScalePan(int iPan);

    static CComPtr<IDirectSound3DListener8> ms_pqListener;
    static wchar_t ms_acPath[FILENAME_MAX];
    static DWORD ms_adw3DMode[];
    
    static const float VOLSCALEFACTOR;
    static const float PANSCALEFACTOR;

    std::map<int,SoundInfo*> m_kSoundMap;
    typedef map<int,SoundInfo*>::iterator SOUNDMAPITERATOR;
};

#include "MADxSoundRenderer.inl"

} // namespace MagicAudio

#endif // #define MADXSOUNDRENDERER_H