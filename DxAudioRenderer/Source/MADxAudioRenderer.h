#ifndef MADXAUDIORENDERER_H
#define MADXAUDIORENDERER_H

#include <dsound.h>
#include <atlbase.h>
#include "MAAudioEffects.h"
#include "MAAudio.h"

namespace MagicAudio
{

class DxAudioRenderer
{
protected:
    DxAudioRenderer ();

    class EffectObjectDesc
    {
    public:
        const GUID* pkClass;
        const GUID* pkInterfaceID;
    };

    static void Initialize (int iWindowID);
    static IDirectSound8* GetDirectSoundObject ();
    static void ReleaseDirectSoundObject ();

    bool UpdateEffects (Audio* pkAudio,AudioEffect::TYPE eType, IDirectSoundBuffer8* pqBuffer,
        IDirectSound3DBuffer8* pq3DBuffer = NULL);

    void UpdateAmpMod (AudioEffect* pkEffect, IUnknown*pqEffect);
    void UpdateChorus (AudioEffect* pkEffect, IUnknown* pqEffect);
    void UpdateCompressor (AudioEffect* pkEffect, IUnknown* pqEffect);
    void UpdateDelay (AudioEffect* pkEffect, IUnknown* pqEffect);
    void UpdateDistortion (AudioEffect* pkEffect, IUnknown* pqEffect);
    void UpdateEnVerb (AudioEffect* pkEffect, IUnknown* pqEffect);
    void UpdateFlanger (AudioEffect* pkEffect, IUnknown* pqEffect);
    void UpdateParamEq (AudioEffect* pkEffect, IUnknown* pqEffect);
    void UpdateReverb (AudioEffect* pkEffect, IUnknown* pqEffect);

    static CComPtr<IDirectSound8> ms_pqDirectSound;
    static bool ms_bInitialized;
    static EffectObjectDesc ms_akEffObjDesc[AudioEffect::QUANTITY];
    static DSEFFECTDESC ms_akEffectDesc[AudioEffect::QUANTITY];
    static DWORD ms_adwEnVerbPreset[];
    static LONG ms_alEnVerbQuality[];
    typedef void (DxAudioRenderer::*ApplyEffect)(AudioEffect* pkEffect, IUnknown* pqUnknown);
    ApplyEffect m_afnApplyEffect[AudioEffect::QUANTITY];
};

} // namespace MagicAudio

#endif // MADXAUDIORENDERER_H