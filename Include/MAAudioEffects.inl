inline AudioEffect::TYPE AudioEffect::Type ()
{   
    return m_eType;
}

///////////////////////////////////////////////////////////////////////////////

inline int AmpModEffect::GetFrequency ()
{
    return m_iFrequency;
}

inline AmpModEffect::WAVEFORM AmpModEffect::GetWaveform ()
{
    return m_eWaveform;
}

///////////////////////////////////////////////////////////////////////////////

inline float ChorusEffect::GetMix ()
{
    return m_fMix;
}

inline float ChorusEffect::GetFeedback ()
{
    return m_fFeedback;
}

inline float ChorusEffect::GetDelay ()
{
    return m_fDelay;
}

inline float ChorusEffect::GetDepth ()
{
    return m_fDepth;
}

inline float ChorusEffect::GetFrequency ()
{
    return m_fFrequency;
}

inline void ChorusEffect::SetWaveform (WAVEFORM eWaveform)
{
    m_eWaveform = eWaveform;
}

inline ChorusEffect::WAVEFORM ChorusEffect::GetWaveform ()
{
    return m_eWaveform;
}

inline void ChorusEffect::SetPhase (PHASE ePhase)
{
    m_ePhase = ePhase;
}

inline ChorusEffect::PHASE ChorusEffect::GetPhase ()
{
    return m_ePhase;
}

///////////////////////////////////////////////////////////////////////////////

inline float CompressorEffect::GetGain ()
{
    return m_fGain;
}

inline float CompressorEffect::GetAttack ()
{
    return m_fAttack;
}

inline float CompressorEffect::GetRelease ()
{
    return m_fRelease;
}

inline float CompressorEffect::GetThreshold ()
{
    return m_fThreshold;
}

inline float CompressorEffect::GetRatio ()
{
    return m_fRatio;
}

inline float CompressorEffect::GetDelay ()
{
    return m_fDelay;
}

///////////////////////////////////////////////////////////////////////////////

inline float DelayEffect::GetMix ()
{
    return m_fMix;
}

inline float DelayEffect::GetRightDelay ()
{
    return m_fRightDelay;
}

inline float DelayEffect::GetLeftDelay ()
{
    return m_fLeftDelay;
}

inline float DelayEffect::GetFeedback ()
{
    return m_fFeedback;
}

inline void DelayEffect::SetPan (bool bPan)
{
    m_bPan = bPan;
}

inline bool DelayEffect::GetPan ()
{
    return m_bPan;
}

///////////////////////////////////////////////////////////////////////////////

inline float DistortionEffect::GetGain ()
{
    return m_fGain;
}

inline float DistortionEffect::GetIntensity ()
{
    return m_fIntensity;
}

inline float DistortionEffect::GetCenter ()
{
    return m_fCenter;
}

inline float DistortionEffect::GetBandwidth ()
{
    return m_fBandwidth;
}


inline float DistortionEffect::GetCutoff ()
{
    return m_fCutoff;
}

///////////////////////////////////////////////////////////////////////////////                                                    

inline long EnVerbEffect::GetRoomAtten ()
{
    return m_lRoomAtten;
}

inline long EnVerbEffect::GetRoomHFAtten ()
{
    return m_lRoomHFAtten;
}

inline long EnVerbEffect::GetReflectAtten ()
{
    return m_lReflectAtten;
}

inline long EnVerbEffect::GetReverbAtten ()
{
    return m_lReverbAtten;
}

inline float EnVerbEffect::GetReflectDelay ()
{
    return m_fReflectDelay;
}

inline float EnVerbEffect::GetReverbDelay ()
{
    return m_fReverbDelay;
}

inline float EnVerbEffect::GetDecayTime () 
{
    return m_fDecayTime;
}

inline float EnVerbEffect::GetDecayTimeHFRatio ()
{
    return m_fDecayTimeHFRatio;
}

inline float EnVerbEffect::GetRolloff ()
{
    return m_fRolloff;
}

inline float EnVerbEffect::GetDiffusion ()
{
    return m_fDiffusion;
}

inline float EnVerbEffect::GetDensity ()
{
    return m_fDensity;
}

inline float EnVerbEffect::GetHFRef ()
{
    return m_fHFRef;
}

inline void EnVerbEffect::SetPreset (EnVerbEffect::PRESET ePreset)
{
    m_ePreset = ePreset;
}

inline EnVerbEffect::PRESET EnVerbEffect::GetPreset ()
{
    return m_ePreset;
}

inline EnVerbEffect::QUALITY EnVerbEffect::GetQuality ()
{
    return m_eQuality;
}

inline bool& EnVerbEffect::UpdateQuality ()
{
    return m_bUpdateQuality;
}

///////////////////////////////////////////////////////////////////////////////

inline float FlangerEffect::GetMix ()
{
    return m_fMix;
}

inline float FlangerEffect::GetFeedback ()
{
    return m_fFeedback;
}

inline float FlangerEffect::GetDelay ()
{
    return m_fDelay;
}

inline float FlangerEffect::GetDepth ()
{
    return m_fDepth;
}

inline float FlangerEffect::GetFrequency ()
{
    return m_fFrequency;
}

inline void FlangerEffect::SetWaveform (WAVEFORM eWaveform)
{
    m_eWaveform = eWaveform;
}

inline FlangerEffect::WAVEFORM FlangerEffect::GetWaveform ()
{
    return m_eWaveform;
}

inline void FlangerEffect::SetPhase (PHASE ePhase)
{
    m_ePhase = ePhase;
}

inline FlangerEffect::PHASE FlangerEffect::GetPhase ()
{
    return m_ePhase;
}

///////////////////////////////////////////////////////////////////////////////

inline float ParametricEqEffect::GetCenter ()
{
    return m_fCenter;
}

inline float ParametricEqEffect::GetBandwidth ()
{
    return m_fBandwidth;
}

inline float ParametricEqEffect::GetGain ()
{
    return m_fGain;
}

///////////////////////////////////////////////////////////////////////////////

inline float ReverbEffect::GetInputGain ()
{
    return m_fInputGain;
}

inline float ReverbEffect::GetMix ()
{
    return m_fMix;
}

inline float ReverbEffect::GetTime ()
{
    return m_fTime;
}

inline float ReverbEffect::GetHFRatio ()
{
    return m_fHFRatio;
}
