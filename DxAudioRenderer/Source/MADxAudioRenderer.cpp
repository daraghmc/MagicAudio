#include "MADxAudioRenderer.h"
#include "MADxAudioUtil.h"

using namespace MagicAudio;

CComPtr<IDirectSound8> DxAudioRenderer::ms_pqDirectSound;
bool DxAudioRenderer::ms_bInitialized = false;

DxAudioRenderer::DxAudioRenderer()
{
    m_afnApplyEffect[AudioEffect::AMPMOD] = &DxAudioRenderer::UpdateAmpMod;
    m_afnApplyEffect[AudioEffect::CHORUS] = &DxAudioRenderer::UpdateChorus;
    m_afnApplyEffect[AudioEffect::COMPRESSOR] = &DxAudioRenderer::UpdateCompressor;
    m_afnApplyEffect[AudioEffect::DELAY] = &DxAudioRenderer::UpdateDelay;
    m_afnApplyEffect[AudioEffect::DISTORTION] = &DxAudioRenderer::UpdateDistortion;
    m_afnApplyEffect[AudioEffect::ENVERB] = &DxAudioRenderer::UpdateEnVerb;
    m_afnApplyEffect[AudioEffect::FLANGER] = &DxAudioRenderer::UpdateFlanger;
    m_afnApplyEffect[AudioEffect::PARAMEQ] = &DxAudioRenderer::UpdateParamEq;
    m_afnApplyEffect[AudioEffect::REVERB] = &DxAudioRenderer::UpdateReverb;
}

void DxAudioRenderer::Initialize (int iWindowID)
{
    if ( ms_bInitialized )
        return;

    HRESULT hr = DirectSoundCreate8(NULL,&ms_pqDirectSound,NULL);
    MA_DXAUDIO_ERR(hr);
    
    hr = ms_pqDirectSound->SetCooperativeLevel((HWND)iWindowID,DSSCL_PRIORITY);
    MA_DXAUDIO_ERR(hr);

    for (int i = 0; i < AudioEffect::QUANTITY; i++)
    {
        ms_akEffectDesc[i].dwSize = sizeof(DSEFFECTDESC);
        ms_akEffectDesc[i].guidDSFXClass = *ms_akEffObjDesc[i].pkClass;
        ms_akEffectDesc[i].dwFlags = 0;
        ms_akEffectDesc[i].dwReserved1 = NULL;
        ms_akEffectDesc[i].dwReserved2 = NULL;
    }
    
    ms_bInitialized = true;
}

IDirectSound8* DxAudioRenderer::GetDirectSoundObject ()
{
    return ms_pqDirectSound;
}

void DxAudioRenderer::ReleaseDirectSoundObject ()
{   
    if ( ms_pqDirectSound != NULL )
        ms_pqDirectSound.Release();
}

