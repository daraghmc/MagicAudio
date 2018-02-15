#include "MAAudioEffects.h"
#include "MAAudio.mcr"

using namespace MagicAudio;

///////////////////////////////////////////////////////////////////////////////

const int AmpModEffect::MIN_FREQ = 1;
const int AmpModEffect::MAX_FREQ = 1000;

AmpModEffect::AmpModEffect ()
{
    m_eType = AMPMOD;
    m_iFrequency = 20;
    m_eWaveform = TRIANGLE;
}

void AmpModEffect::SetFrequency (int iFrequency)
{
    MAAUDIO_CLAMP(iFrequency,MIN_FREQ,MAX_FREQ);
    m_iFrequency = iFrequency;
}

void AmpModEffect::SetWaveform (AmpModEffect::WAVEFORM eWaveform)
{
    m_eWaveform = eWaveform;
}

///////////////////////////////////////////////////////////////////////////////

const float ChorusEffect::MIN_MIX = 0.0f;
const float ChorusEffect::MAX_MIX = 100.0f;
const float ChorusEffect::MIN_DELAY = 0.0f;
const float ChorusEffect::MAX_DELAY = 20.0f;
const float ChorusEffect::MIN_FEEDBACK = -99.0f;
const float ChorusEffect::MAX_FEEDBACK = 99.0f;
const float ChorusEffect::MIN_DEPTH = 0.0f;
const float ChorusEffect::MAX_DEPTH = 100.0f;
const float ChorusEffect::MIN_FREQ = 0.0f;
const float ChorusEffect::MAX_FREQ = 10.0f;

ChorusEffect::ChorusEffect ()
{
    m_eType = CHORUS;
    m_ePhase = POS_90; 
    m_eWaveform = SINE;
    m_fDelay = 16.0f;
    m_fDepth = 10.0f;
    m_fFeedback = 25.0f;
    m_fFrequency = 1.1f;
    m_fMix = 50.0f;
}

void ChorusEffect::SetMix (float fMix)
{
    MAAUDIO_CLAMP(fMix,MIN_MIX,MAX_MIX);
    m_fMix = fMix;
}

void ChorusEffect::SetFeedback (float fFeedback)
{
    MAAUDIO_CLAMP(fFeedback,MIN_FEEDBACK,MAX_FEEDBACK);
    m_fFeedback = fFeedback;
}

void ChorusEffect::SetDelay (float fDelay)
{
    MAAUDIO_CLAMP(fDelay,MIN_DELAY,MAX_DELAY);
    m_fDelay = fDelay;
}

void ChorusEffect::SetDepth (float fDepth)
{
    MAAUDIO_CLAMP(fDepth,MIN_DEPTH,MAX_DEPTH);
    m_fDepth = fDepth;
}

void ChorusEffect::SetFrequency (float fFrequency)
{
    MAAUDIO_CLAMP(fFrequency,MIN_FREQ,MAX_FREQ);
    m_fFrequency = fFrequency;
}

///////////////////////////////////////////////////////////////////////////////

const float CompressorEffect::MIN_GAIN = -60.0f;
const float CompressorEffect::MAX_GAIN = 60.0f;
const float CompressorEffect::MIN_ATTACK = 0.01f;
const float CompressorEffect::MAX_ATTACK = 500.0f;
const float CompressorEffect::MIN_RELEASE = 50.0f;
const float CompressorEffect::MAX_RELEASE = 3000.0f;
const float CompressorEffect::MIN_THRESHOLD = -60.0f;
const float CompressorEffect::MAX_THRESHOLD = 0.0f;
const float CompressorEffect::MIN_RATIO = 1.0f;
const float CompressorEffect::MAX_RATIO = 100.0f;
const float CompressorEffect::MIN_DELAY = 0.0f;
const float CompressorEffect::MAX_DELAY  = 4.0f;

CompressorEffect::CompressorEffect ()
{
    m_eType = COMPRESSOR;
    m_fGain = 0.0f;
    m_fAttack = 10.0f;
    m_fRelease = 200.0f;
    m_fThreshold= -20.0f;
    m_fRatio = 3.0f;
    m_fDelay = 4.0f;
}

void CompressorEffect::SetGain (float fGain)
{
    MAAUDIO_CLAMP(fGain,MIN_GAIN,MAX_GAIN);
    m_fGain = fGain;
}

void CompressorEffect::SetAttack (float fAttack)
{
    MAAUDIO_CLAMP(fAttack,MIN_ATTACK,MAX_ATTACK);
    m_fAttack = fAttack;
}

void CompressorEffect::SetRelease (float fRelease)
{
    MAAUDIO_CLAMP(fRelease,MIN_RELEASE,MAX_RELEASE);
    m_fRelease = fRelease;
}

void CompressorEffect::SetThreshold (float fThreshold)
{
    MAAUDIO_CLAMP(fThreshold,MIN_THRESHOLD,MAX_THRESHOLD);
    m_fThreshold = fThreshold;
}

void CompressorEffect::SetRatio (float fRatio)
{
    MAAUDIO_CLAMP(fRatio,MIN_RATIO,MAX_RATIO);
    m_fRatio = fRatio;
}

void CompressorEffect::SetDelay (float fDelay)
{
    MAAUDIO_CLAMP(fDelay,MIN_DELAY,MAX_DELAY);
    m_fDelay = fDelay;
}

///////////////////////////////////////////////////////////////////////////////

const float DelayEffect::MAX_MIX = 100.0f;
const float DelayEffect::MIN_MIX = 0.0f;
const float DelayEffect::MIN_FEEDBACK = 0.0f;
const float DelayEffect::MAX_FEEDBACK = 100.0f;
const float DelayEffect::MIN_DELAY = 1.0f;
const float DelayEffect::MAX_DELAY = 2000.0f;

DelayEffect::DelayEffect ()
{
    m_eType = DELAY;
    m_fMix = 50.0f;
    m_fRightDelay = m_fLeftDelay = 500.0f;
    m_fFeedback = 50.0f;
    m_bPan = false;
}

void DelayEffect::SetMix (float fMix)
{
    MAAUDIO_CLAMP(fMix,MIN_MIX,MAX_MIX);
    m_fMix = fMix;
}

void DelayEffect::SetDelay (float fDelay)
{
    MAAUDIO_CLAMP(fDelay,MIN_DELAY,MAX_DELAY);
    m_fRightDelay = m_fLeftDelay = fDelay;
}

void DelayEffect::SetRightDelay (float fDelay)
{
    MAAUDIO_CLAMP(fDelay,MIN_DELAY,MAX_DELAY);
    m_fRightDelay = fDelay;    
}

void DelayEffect::SetLeftDelay (float fDelay)
{
    MAAUDIO_CLAMP(fDelay,MIN_DELAY,MAX_DELAY);
    m_fLeftDelay = fDelay;  
}

void DelayEffect::SetFeedback (float fFeedback)
{
    MAAUDIO_CLAMP(fFeedback,MIN_FEEDBACK,MAX_FEEDBACK);
    m_fRightDelay = fFeedback;  
}

///////////////////////////////////////////////////////////////////////////////

const float DistortionEffect::MIN_GAIN = -60.0f;
const float DistortionEffect::MAX_GAIN = 0.0f;
const float DistortionEffect::MIN_CENTER = 100.0f;
const float DistortionEffect::MAX_CENTER = 8000.0f;
const float DistortionEffect::MIN_INTENSITY = 0.0f;
const float DistortionEffect::MAX_INTENSITY = 100.0f;
const float DistortionEffect::MIN_BANDWIDTH = 100.0f;
const float DistortionEffect::MAX_BANDWIDTH = 8000.0f;
const float DistortionEffect::MIN_CUTOFF = 100.0f;
const float DistortionEffect::MAX_CUTOFF = 8000.0f;

DistortionEffect::DistortionEffect ()
{
    m_eType = DISTORTION;
    m_fGain = -18.0f;
    m_fIntensity = 15.0f;
    m_fCenter = 2400.0f;
    m_fBandwidth = 2400.0f;
    m_fCutoff = 8000.0f;
}

void DistortionEffect::SetGain (float fGain)
{
    MAAUDIO_CLAMP(fGain,MIN_GAIN,MAX_GAIN);
    m_fGain = fGain;
}

void DistortionEffect::SetIntensity (float fIntensity)
{
    MAAUDIO_CLAMP(fIntensity,MIN_INTENSITY,MAX_INTENSITY);
    m_fIntensity = fIntensity;
}

void DistortionEffect::SetCenter (float fCenter)
{
    MAAUDIO_CLAMP(fCenter,MIN_CENTER,MAX_CENTER);
    m_fCenter = fCenter;
}

void DistortionEffect::SetBandwidth (float fBandwidth)
{
    MAAUDIO_CLAMP(fBandwidth,MIN_BANDWIDTH,MAX_BANDWIDTH);
    m_fBandwidth = fBandwidth;
}

void DistortionEffect::SetCutoff (float fCutoff)
{
    MAAUDIO_CLAMP(fCutoff,MIN_CUTOFF,MAX_CUTOFF);
    m_fCutoff = fCutoff;
}

///////////////////////////////////////////////////////////////////////////////                                                    
                           
const long EnVerbEffect::MIN_ROOMATTEN = -10000;
const long EnVerbEffect::MAX_ROOMATTEN = 0;
const long EnVerbEffect::MIN_ROOMHFATTEN = -10000;
const long EnVerbEffect::MAX_ROOMHFATTEN = 0;
const long EnVerbEffect::MIN_REFLECTATTEN = -10000;
const long EnVerbEffect::MAX_REFLECTATTEN = 1000;
const long EnVerbEffect::MIN_REVERBATTEN = -10000;
const long EnVerbEffect::MAX_REVERBATTEN = 2000;
const float EnVerbEffect::MIN_REFLECTDELAY = 0.0f;
const float EnVerbEffect::MAX_REFLECTDELAY = 0.3f;
const float EnVerbEffect::MIN_REVERBDELAY = 0.0f;
const float EnVerbEffect::MAX_REVERBDELAY = 0.1f;
const float EnVerbEffect::MIN_DECAYTIME = 0.1f;
const float EnVerbEffect::MAX_DECAYTIME = 20.0f;
const float EnVerbEffect::MIN_DECAYTIMEHFRATIO = 0.1f;
const float EnVerbEffect::MAX_DECAYTIMEHFRATIO = 2.0f;
const float EnVerbEffect::MIN_ROLLOFF = 0.0f;
const float EnVerbEffect::MAX_ROLLOFF = 10.0f;
const float EnVerbEffect::MIN_DIFFUSION = 0.0f;
const float EnVerbEffect::MAX_DIFFUSION = 100.0f;
const float EnVerbEffect::MIN_DENSITY = 0.0f;
const float EnVerbEffect::MAX_DENSITY = 100.0f;
const float EnVerbEffect::MIN_HFREF = 20.0f;
const float EnVerbEffect::MAX_HFREF = 20000.0f;
 
EnVerbEffect::EnVerbEffect()
{
    m_eType = ENVERB;
    m_lRoomAtten = -100;
    m_lRoomHFAtten = -100;
    m_lReflectAtten = -2600;
    m_lReverbAtten = 200;
    m_fReflectDelay = 0.007f;
    m_fReverbDelay = 0.011f;
    m_fDecayTime = 1.5f;
    m_fDecayTimeHFRatio = 0.83f;
    m_fDensity = 100.0f;
    m_fDiffusion = 100.0f;
    m_fRolloff = 0.0f;
    m_fHFRef = 5000.0f;
    m_ePreset = NONE;
    m_eQuality = MEDIUM;
    m_bUpdateQuality = true;
}

void EnVerbEffect::SetRoomAtten (long lAtten)
{
    MAAUDIO_CLAMP(lAtten,MIN_ROOMATTEN,MAX_ROOMATTEN);
    m_lRoomAtten = lAtten;
}

void EnVerbEffect::SetRoomHFAtten (long lAtten)
{
    MAAUDIO_CLAMP(lAtten,MIN_ROOMHFATTEN,MAX_ROOMHFATTEN);
    m_lRoomHFAtten = lAtten;
}

void EnVerbEffect::SetReflectAtten (long lAtten)
{
    MAAUDIO_CLAMP(lAtten,MIN_REFLECTATTEN,MAX_REFLECTATTEN);
    m_lReflectAtten = lAtten;
}

void EnVerbEffect::SetReverbAtten (long lAtten)
{
    MAAUDIO_CLAMP(lAtten,MIN_REVERBATTEN,MAX_REVERBATTEN);
    m_lReverbAtten = lAtten;
}

void EnVerbEffect::SetReflectDelay (float fDelay)
{
    MAAUDIO_CLAMP(fDelay,MIN_REFLECTDELAY,MAX_REFLECTDELAY);
    m_fReflectDelay = fDelay;
}

void EnVerbEffect::SetReverbDelay (float fDelay)
{
    MAAUDIO_CLAMP(fDelay,MIN_REVERBDELAY,MAX_REVERBDELAY);
    m_fReverbDelay = fDelay;    
}

void EnVerbEffect::SetDecayTime (float fTime)
{
    MAAUDIO_CLAMP(fTime,MIN_DECAYTIME,MAX_DECAYTIME);   
    m_fDecayTime = fTime;
}

void EnVerbEffect::SetDecayTimeHFRatio (float fRatio)
{
    MAAUDIO_CLAMP(fRatio,MIN_DECAYTIMEHFRATIO,MAX_DECAYTIMEHFRATIO);       
    m_fDecayTimeHFRatio = fRatio;
}

void EnVerbEffect::SetRolloff (float fRolloff)
{
    MAAUDIO_CLAMP(fRolloff,MIN_ROLLOFF,MAX_ROLLOFF);
    m_fRolloff = fRolloff;
}

void EnVerbEffect::SetDiffusion (float fDiffusion)
{
    MAAUDIO_CLAMP(fDiffusion,MIN_DIFFUSION,MAX_DIFFUSION);
    m_fDiffusion = fDiffusion;
}

void EnVerbEffect::SetDensity (float fDensity)
{
    MAAUDIO_CLAMP(fDensity, MIN_DENSITY, MAX_DENSITY);
    m_fDensity = fDensity;
}

void EnVerbEffect::SetHFRef (float fHFRef)
{
    MAAUDIO_CLAMP(fHFRef,MIN_HFREF,MAX_HFREF);
    m_fHFRef = fHFRef;
}

void EnVerbEffect::SetQuality (EnVerbEffect::QUALITY eQuality)
{
    if ( eQuality != m_eQuality )
    {
        m_bUpdateQuality = true;
        m_eQuality = eQuality;
    }
}

///////////////////////////////////////////////////////////////////////////////

const float FlangerEffect::MIN_MIX = 0.0f;
const float FlangerEffect::MAX_MIX = 100.0f;
const float FlangerEffect::MIN_DELAY = 0.0f;
const float FlangerEffect::MAX_DELAY = 4.0f;
const float FlangerEffect::MIN_FEEDBACK = -99.0f;
const float FlangerEffect::MAX_FEEDBACK = 99.0f;
const float FlangerEffect::MIN_DEPTH = 0.0f;
const float FlangerEffect::MAX_DEPTH = 100.0f;
const float FlangerEffect::MIN_FREQ = 0.0f;
const float FlangerEffect::MAX_FREQ = 10.0f;

FlangerEffect::FlangerEffect ()
{
    m_eType = FLANGER;
    m_ePhase = ZERO; 
    m_eWaveform = SINE;
    m_fDelay = 2.0f;
    m_fDepth = 100.0f;
    m_fFeedback = 50.0f;
    m_fFrequency = 0.25f;
    m_fMix = 50.0f;
}

void FlangerEffect::SetMix (float fMix)
{
    MAAUDIO_CLAMP(fMix,MIN_MIX,MAX_MIX);
    m_fMix = fMix;
}

void FlangerEffect::SetFeedback (float fFeedback)
{
    MAAUDIO_CLAMP(fFeedback,MIN_FEEDBACK,MAX_FEEDBACK);
    m_fFeedback = fFeedback;
}

void FlangerEffect::SetDelay (float fDelay)
{
    MAAUDIO_CLAMP(fDelay,MIN_DELAY,MAX_DELAY);
    m_fDelay = fDelay;
}

void FlangerEffect::SetDepth (float fDepth)
{
    MAAUDIO_CLAMP(fDepth,MIN_DEPTH,MAX_DEPTH);
    m_fDepth = fDepth;
}

void FlangerEffect::SetFrequency (float fFrequency)
{
    MAAUDIO_CLAMP(fFrequency,MIN_FREQ,MAX_FREQ);
    m_fFrequency = fFrequency;
}

///////////////////////////////////////////////////////////////////////////////

const float ParametricEqEffect::MIN_GAIN = -15.0f;
const float ParametricEqEffect::MAX_GAIN = 15.0f;
const float ParametricEqEffect::MIN_CENTER = 80.0f;
const float ParametricEqEffect::MAX_CENTER = 16000.0f;
const float ParametricEqEffect::MIN_BANDWIDTH = 1.0f;
const float ParametricEqEffect::MAX_BANDWIDTH = 36.0f;

ParametricEqEffect::ParametricEqEffect ()
{
    m_eType = PARAMEQ;
    m_fCenter = 8000.0f;
    m_fBandwidth = 12.0f;
    m_fGain = 0.0f;
}

void ParametricEqEffect::SetCenter (float fCenter)
{
    MAAUDIO_CLAMP(fCenter,MIN_CENTER,MAX_CENTER);
    m_fCenter = fCenter;
}

void ParametricEqEffect::SetBandwidth (float fBandwidth)
{
    MAAUDIO_CLAMP(fBandwidth,MIN_BANDWIDTH,MAX_BANDWIDTH);
    m_fBandwidth = fBandwidth;
}

void ParametricEqEffect::SetGain (float fGain)
{
    MAAUDIO_CLAMP(fGain,MIN_GAIN,MAX_GAIN);
    m_fGain = fGain;
}

///////////////////////////////////////////////////////////////////////////////

const float ReverbEffect::MIN_TIME = 0.001f;
const float ReverbEffect::MAX_TIME = 3000.0f;
const float ReverbEffect::MIN_GAIN = -96.0f;
const float ReverbEffect::MAX_GAIN = 0.0f;
const float ReverbEffect::MIN_MIX = -96.0f;
const float ReverbEffect::MAX_MIX = 0.0f;
const float ReverbEffect::MIN_HFRATIO = 0.001f;
const float ReverbEffect::MAX_HFRATIO = 0.999f;

ReverbEffect::ReverbEffect ()
{
    m_eType = REVERB;
    m_fTime = 1000.0f;
    m_fInputGain = MAX_GAIN;
    m_fMix = MAX_MIX;
    m_fHFRatio = MIN_HFRATIO;
}

void ReverbEffect::SetInputGain (float fGain)
{
    MAAUDIO_CLAMP(fGain,MIN_GAIN,MAX_GAIN);
    m_fInputGain = fGain;
}

void ReverbEffect::SetMix (float fMix)
{
    MAAUDIO_CLAMP(fMix,MIN_MIX,MAX_MIX);
    m_fMix = fMix;
}

void ReverbEffect::SetTime (float fTime)
{
    MAAUDIO_CLAMP(fTime,MIN_TIME,MAX_TIME);
    m_fTime = fTime;
}

void ReverbEffect::SetHFRatio (float fRatio)
{
    MAAUDIO_CLAMP(fRatio,MIN_HFRATIO,MAX_HFRATIO);
    m_fHFRatio = fRatio;
}
