#include "MADxAudioRenderer.h"
#include "MADxAudioUtil.h"

using namespace MagicAudio;

DxAudioRenderer::EffectObjectDesc DxAudioRenderer::ms_akEffObjDesc[] =
{
    {&GUID_DSFX_STANDARD_GARGLE, &IID_IDirectSoundFXGargle8},
    {&GUID_DSFX_STANDARD_CHORUS, &IID_IDirectSoundFXChorus8}, 
    {&GUID_DSFX_STANDARD_COMPRESSOR, &IID_IDirectSoundFXCompressor8},
    {&GUID_DSFX_STANDARD_ECHO, &IID_IDirectSoundFXEcho8}, 
    {&GUID_DSFX_STANDARD_DISTORTION, &IID_IDirectSoundFXDistortion8},
    {&GUID_DSFX_STANDARD_I3DL2REVERB, &IID_IDirectSoundFXI3DL2Reverb8},
    {&GUID_DSFX_STANDARD_FLANGER, &IID_IDirectSoundFXFlanger8},
    {&GUID_DSFX_STANDARD_PARAMEQ, &IID_IDirectSoundFXParamEq8},
    {&GUID_DSFX_WAVES_REVERB, &IID_IDirectSoundFXWavesReverb8}
};

DWORD DxAudioRenderer::ms_adwEnVerbPreset[] = 
{
    DSFX_I3DL2_ENVIRONMENT_PRESET_ALLEY,
    DSFX_I3DL2_ENVIRONMENT_PRESET_ARENA, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_AUDITORIUM, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_BATHROOM, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_CARPETEDHALLWAY, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_CAVE, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_CITY,
    DSFX_I3DL2_ENVIRONMENT_PRESET_CONCERTHALL, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_DEFAULT, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_FOREST, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_GENERIC,
    DSFX_I3DL2_ENVIRONMENT_PRESET_HALLWAY, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_HANGAR, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_LARGEHALL, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_LARGEROOM, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_LIVINGROOM, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_MEDIUMHALL, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_MEDIUMROOM, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_MOUNTAINS, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_PADDEDCELL, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_PARKINGLOT,
    DSFX_I3DL2_ENVIRONMENT_PRESET_PLAIN, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_PLATE,        
    DSFX_I3DL2_ENVIRONMENT_PRESET_QUARRY, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_ROOM, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_SEWERPIPE, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_SMALLROOM, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_STONEROOM, 
    DSFX_I3DL2_ENVIRONMENT_PRESET_UNDERWATER   
};

LONG DxAudioRenderer::ms_alEnVerbQuality[] = 
{
    DSFX_I3DL2REVERB_QUALITY_MIN,
    DSFX_I3DL2REVERB_QUALITY_DEFAULT,
    DSFX_I3DL2REVERB_QUALITY_MAX 
};

DSEFFECTDESC DxAudioRenderer::ms_akEffectDesc[AudioEffect::QUANTITY];

bool DxAudioRenderer::UpdateEffects (Audio* pkAudio, AudioEffect::TYPE eType, 
    IDirectSoundBuffer8* pqBuffer, IDirectSound3DBuffer8* pq3DBuffer)
{
    HRESULT hr;
    
    bool bNeedApply = false;
   
    if ( eType != AudioEffect::NONE )
    {
        AudioEffect* pkEffect = pkAudio->GetEffect(eType);
        if ( pkEffect == NULL )
            return false;

        CComPtr<IUnknown> pqInterface;
        hr = pqBuffer->GetObjectInPath(*ms_akEffObjDesc[(int)eType].pkClass,0,
            *ms_akEffObjDesc[eType].pkInterfaceID, (void**)&pqInterface);

        if ( hr != DSERR_OBJECTNOTFOUND )
            MA_DXAUDIO_ERR(hr);

        if ( pqInterface != NULL )
        {
            (this->*m_afnApplyEffect[eType])(pkEffect,pqInterface);
            return true;
        }
        else
        {
            bNeedApply = true;
        }
    }

    vector<AudioEffect*> kEffects = pkAudio->GetEffects();
    if ( kEffects.size() == 0 )
    {
        pqBuffer->SetFX(0,NULL,NULL);
        return true;
    }

    if ( !bNeedApply )
    {
        CComPtr<IUnknown> pqInterface;
        for (int i = 0; i < (int)kEffects.size(); i++)
        {
            hr = pqBuffer->GetObjectInPath(*ms_akEffObjDesc[i].pkClass,0,
                *ms_akEffObjDesc[i].pkInterfaceID,(void**)&pqInterface); 

            if ( hr != DSERR_OBJECTNOTFOUND )
                MA_DXAUDIO_ERR(hr);

            if ( pqInterface == NULL )
            {
                bNeedApply = true;
                break;
            }
        }
    }
 
    if ( bNeedApply )
    {
        DSEFFECTDESC* akDesc = new DSEFFECTDESC[kEffects.size()];
        for (int i = 0; i < (int)kEffects.size(); i++)
        {
            memcpy(&akDesc[i], &ms_akEffectDesc[(int)kEffects[i]->Type()], 
                sizeof(DSEFFECTDESC));
        }

        hr = pqBuffer->SetFX(kEffects.size(),akDesc,NULL);
        delete akDesc;
        MA_DXAUDIO_WARN(hr);
    }

    for (int i = 0; i < (int)kEffects.size(); i++)
    {
        int iType = kEffects[i]->Type();
        CComPtr<IUnknown> pqInterface;    
        hr = pqBuffer->GetObjectInPath(*ms_akEffObjDesc[iType].pkClass,0,
            *ms_akEffObjDesc[iType].pkInterfaceID,
            (void**)&pqInterface); 
        if ( hr != DSERR_OBJECTNOTFOUND )
            MA_DXAUDIO_ERR(hr);
        (this->*m_afnApplyEffect[iType])(kEffects[i], pqInterface);
    }

    return true;
}

void DxAudioRenderer::UpdateAmpMod (AudioEffect* pkEffect, IUnknown* pqEffect)
{
    AmpModEffect* pkAmpMod = (AmpModEffect*)pkEffect;
    IDirectSoundFXGargle8* pqGargle = (IDirectSoundFXGargle8*)pqEffect;

    DSFXGargle kParams;
    kParams.dwRateHz = pkAmpMod->GetFrequency();
    kParams.dwWaveShape = pkAmpMod->GetWaveform();
    
    HRESULT hr = pqGargle->SetAllParameters(&kParams);
    MA_DXAUDIO_ERR(hr);
}

void DxAudioRenderer::UpdateChorus (AudioEffect* pkEffect, IUnknown* pqEffect)
{
    ChorusEffect* pkChorus = (ChorusEffect*)pkEffect;
    IDirectSoundFXChorus8* pqChorus = (IDirectSoundFXChorus8*)pqEffect;

    DSFXChorus kParams;
    kParams.fWetDryMix = pkChorus->GetMix();
    kParams.fDepth = pkChorus->GetDepth();
    kParams.fDelay = pkChorus->GetDelay();
    kParams.fFeedback = pkChorus->GetFeedback();
    kParams.fFrequency = pkChorus->GetFrequency();
    kParams.lPhase = (LONG)pkChorus->GetPhase();
    kParams.lWaveform = (LONG)pkChorus->GetWaveform();

    HRESULT hr = pqChorus->SetAllParameters(&kParams);
    MA_DXAUDIO_ERR(hr);
}

void DxAudioRenderer::UpdateCompressor (AudioEffect* pkEffect, IUnknown* pqEffect)
{
    CompressorEffect* pkCompressor = (CompressorEffect*)pkEffect;
    IDirectSoundFXCompressor8* pqCompressor = (IDirectSoundFXCompressor8*)pqEffect;

    DSFXCompressor kParams;
    kParams.fGain = pkCompressor->GetGain();
    kParams.fAttack = pkCompressor->GetAttack();
    kParams.fRelease = pkCompressor->GetRelease();
    kParams.fPredelay = pkCompressor->GetDelay();
    kParams.fRatio = pkCompressor->GetRatio();
    kParams.fThreshold = pkCompressor->GetThreshold();

    HRESULT hr = pqCompressor->SetAllParameters(&kParams);
    MA_DXAUDIO_ERR(hr);
}

void DxAudioRenderer::UpdateDelay (AudioEffect* pkEffect, IUnknown* pqEffect)
{
    DelayEffect* pkDelay = (DelayEffect*)pkEffect;
    IDirectSoundFXEcho8* pqDelay = (IDirectSoundFXEcho8*)pqEffect;

    DSFXEcho kParams;
    kParams.fWetDryMix = pkDelay->GetMix();
    kParams.fLeftDelay = pkDelay->GetLeftDelay();
    kParams.fRightDelay = pkDelay->GetRightDelay();
    kParams.fFeedback = pkDelay->GetFeedback();
    kParams.lPanDelay = pkDelay->GetPan();

    HRESULT hr = pqDelay->SetAllParameters(&kParams);
    MA_DXAUDIO_ERR(hr);
}

void DxAudioRenderer::UpdateDistortion (AudioEffect* pkEffect, IUnknown* pqEffect)
{
    DistortionEffect* pkDistortion = (DistortionEffect*)pkEffect;
    IDirectSoundFXDistortion8* pqDistortion = (IDirectSoundFXDistortion8*)pqEffect;   

    DSFXDistortion kParams;
    
    kParams.fGain = pkDistortion->GetGain();
    kParams.fEdge = pkDistortion->GetIntensity();
    kParams.fPostEQCenterFrequency = pkDistortion->GetCenter();
    kParams.fPostEQBandwidth = pkDistortion->GetBandwidth();
    kParams.fPreLowpassCutoff = pkDistortion->GetCutoff();

    HRESULT hr = pqDistortion->SetAllParameters(&kParams);
    MA_DXAUDIO_ERR(hr);
}

void DxAudioRenderer::UpdateEnVerb (AudioEffect* pkEffect, IUnknown* pqEffect)
{
    EnVerbEffect* pkEnVerb = (EnVerbEffect*)pkEffect;
    IDirectSoundFXI3DL2Reverb8* pqEnVerb = (IDirectSoundFXI3DL2Reverb8*)pqEffect;

    if ( pkEnVerb->GetPreset() != EnVerbEffect::NONE)
    {
        HRESULT hr = pqEnVerb->SetPreset(ms_adwEnVerbPreset[pkEnVerb->GetPreset()]);
        MA_DXAUDIO_ERR(hr);
        if ( pkEnVerb->UpdateQuality() )
        {
            hr = pqEnVerb->SetQuality((long)pkEnVerb->GetQuality());
            pkEnVerb->UpdateQuality() = false;
            MA_DXAUDIO_WARN(hr);
        }
        return;
    }

    DSFXI3DL2Reverb kParams;
    kParams.lRoom = pkEnVerb->GetRoomAtten();
    kParams.lReflections = pkEnVerb->GetReflectAtten();
    kParams.lReverb = pkEnVerb->GetReverbAtten();
    kParams.lRoomHF = pkEnVerb->GetRoomHFAtten();
    kParams.flReflectionsDelay = pkEnVerb->GetReflectDelay();
    kParams.flReverbDelay = pkEnVerb->GetReverbDelay();
    kParams.flDecayTime = pkEnVerb->GetDecayTime();
    kParams.flDecayHFRatio = pkEnVerb->GetDecayTimeHFRatio();
    kParams.flRoomRolloffFactor = pkEnVerb->GetRolloff();
    kParams.flDiffusion = pkEnVerb->GetDiffusion();
    kParams.flDensity = pkEnVerb->GetDensity();
    kParams.flHFReference = pkEnVerb->GetHFRef();

    HRESULT hr;

    if ( pkEnVerb->UpdateQuality() )
    {
        hr = pqEnVerb->SetQuality(ms_alEnVerbQuality[pkEnVerb->GetQuality()]);
        pkEnVerb->UpdateQuality() = false;
        MA_DXAUDIO_WARN(hr);
    }
    
    hr = pqEnVerb->SetAllParameters(&kParams);
    MA_DXAUDIO_ERR(hr);
}

void DxAudioRenderer::UpdateFlanger (AudioEffect* pkEffect, IUnknown* pqEffect)
{
    FlangerEffect* pkFlanger = (FlangerEffect*)pkEffect;
    IDirectSoundFXFlanger8* pqFlanger = (IDirectSoundFXFlanger8*)pqEffect;

    DSFXFlanger kParams;
    kParams.fWetDryMix = pkFlanger->GetMix();
    kParams.fDepth = pkFlanger->GetDepth();
    kParams.fDelay = pkFlanger->GetDelay();
    kParams.fFeedback = pkFlanger->GetFeedback();
    kParams.fFrequency = pkFlanger->GetFrequency();
    kParams.lPhase = (LONG)pkFlanger->GetPhase();
    kParams.lWaveform = (LONG)pkFlanger->GetWaveform();

    HRESULT hr = pqFlanger->SetAllParameters(&kParams);
    MA_DXAUDIO_ERR(hr);
}

void DxAudioRenderer::UpdateParamEq (AudioEffect* pkEffect, IUnknown* pqEffect)
{
    ParametricEqEffect* pkParamEq = (ParametricEqEffect*)pkEffect;
    IDirectSoundFXParamEq8* pqParamEq = (IDirectSoundFXParamEq8*)pqEffect;

    DSFXParamEq kParams;
    kParams.fCenter = pkParamEq->GetCenter();
    kParams.fBandwidth = pkParamEq->GetBandwidth();
    kParams.fGain = pkParamEq->GetGain();

    HRESULT hr = pqParamEq->SetAllParameters(&kParams);
    MA_DXAUDIO_ERR(hr);
}

void DxAudioRenderer::UpdateReverb (AudioEffect* pkEffect, IUnknown* pqEffect)
{
    ReverbEffect* pkReverb = (ReverbEffect*)pkEffect;
    IDirectSoundFXWavesReverb8* pqReverb = (IDirectSoundFXWavesReverb8*)pqEffect;

    DSFXWavesReverb kParams;  

    kParams.fReverbTime = pkReverb->GetTime();
    kParams.fInGain = pkReverb->GetInputGain();
    kParams.fReverbMix = pkReverb->GetMix();
    kParams.fHighFreqRTRatio = pkReverb->GetHFRatio();
    
    HRESULT hr = pqReverb->SetAllParameters(&kParams);
    MA_DXAUDIO_ERR(hr);
}
