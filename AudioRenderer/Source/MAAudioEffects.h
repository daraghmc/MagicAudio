#ifndef _MAAUDIOEFFECTS_H
#define _MAAUDIOEFFECTS_H

namespace MagicAudio
{

class AudioEffect
{
public:
    enum TYPE
    {
        NONE = -1,
        AMPMOD,
        CHORUS,
        COMPRESSOR,
        DELAY,
        DISTORTION,
        ENVERB,
        FLANGER,
        PARAMEQ,
        REVERB,
        QUANTITY
    };

    TYPE Type ();

protected:
    TYPE m_eType;
};

///////////////////////////////////////////////////////////////////////////////

class AmpModEffect : public AudioEffect
{
public:
    AmpModEffect ();
   
    enum WAVEFORM
    {
        TRIANGLE = 0,
        SQUARE
    };

    void SetFrequency (int iFrequency);
    int GetFrequency ();
    WAVEFORM GetWaveform ();
    void SetWaveform (WAVEFORM eWaveform);

    static const int MIN_FREQ;
    static const int MAX_FREQ;

protected:
    int m_iFrequency;
    WAVEFORM m_eWaveform;
};

///////////////////////////////////////////////////////////////////////////////

class ChorusEffect : public AudioEffect
{
public:
    ChorusEffect ();

    enum WAVEFORM
    {
        SINE = 0,
        TRIANGLE
    };

    enum PHASE
    {
        NEG_180 = 0,
        NEG_90,
        ZERO,
        POS_90,
        POS_180
    };

    void SetMix (float fMix);
    float GetMix ();
    void SetFeedback (float fFeedback);
    float GetFeedback ();
    void SetDelay (float fDelay);
    float GetDelay ();
    void SetDepth (float fDepth);
    float GetDepth ();
    void SetFrequency (float fFrequency);
    float GetFrequency ();
    void SetWaveform (WAVEFORM eWaveform);
    WAVEFORM GetWaveform ();
    void SetPhase (PHASE ePhase);
    PHASE GetPhase ();

    static const float MAX_MIX;
    static const float MIN_MIX;
    static const float MIN_FEEDBACK;
    static const float MAX_FEEDBACK;
    static const float MIN_DELAY;
    static const float MAX_DELAY;
    static const float MIN_DEPTH;
    static const float MAX_DEPTH;
    static const float MIN_FREQ;
    static const float MAX_FREQ;

protected:
    float m_fMix;
    float m_fDepth;
    float m_fFeedback;
    float m_fFrequency;
    float m_fDelay;
    WAVEFORM m_eWaveform;
    PHASE m_ePhase;
};

///////////////////////////////////////////////////////////////////////////////

class CompressorEffect : public AudioEffect
{
public:
    CompressorEffect ();

    void SetGain (float fGain);
    float GetGain ();
    void SetAttack (float fAttack);
    float GetAttack ();
    void SetRelease (float fRelease);
    float GetRelease ();
    void SetThreshold (float fThreshold);
    float GetThreshold ();
    void SetRatio (float fRatio);
    float GetRatio ();
    void SetDelay (float fDelay);
    float GetDelay ();

    static const float MIN_GAIN;
    static const float MAX_GAIN;
    static const float MIN_ATTACK;
    static const float MAX_ATTACK;
    static const float MIN_RELEASE;
    static const float MAX_RELEASE;
    static const float MIN_THRESHOLD;
    static const float MAX_THRESHOLD;
    static const float MIN_RATIO;
    static const float MAX_RATIO;
    static const float MIN_DELAY;
    static const float MAX_DELAY;

protected:
    float m_fGain;
    float m_fAttack;
    float m_fRelease;
    float m_fThreshold;
    float m_fRatio;
    float m_fDelay;
};

///////////////////////////////////////////////////////////////////////////////

class DelayEffect : public AudioEffect
{
public:
    DelayEffect ();

    void SetMix (float fMix);
    float GetMix ();
    void SetDelay (float fDelay);
    void SetRightDelay (float fDelay);
    float GetRightDelay();
    void SetLeftDelay (float fDelay);
    float GetLeftDelay ();
    void SetFeedback (float fFeedback);
    float GetFeedback ();
    void SetPan (bool bPan);
    bool GetPan ();

    static const float MAX_MIX;
    static const float MIN_MIX;
    static const float MIN_FEEDBACK;
    static const float MAX_FEEDBACK;
    static const float MIN_DELAY;
    static const float MAX_DELAY;

protected:
    float m_fMix;
    float m_fFeedback;
    float m_fLeftDelay;
    float m_fRightDelay;   
    bool m_bPan;
};

///////////////////////////////////////////////////////////////////////////////

class DistortionEffect : public AudioEffect
{
public:
    DistortionEffect();

    void SetGain (float fGain);
    float GetGain ();
    void SetIntensity (float fIntensity);
    float GetIntensity ();
    void SetCenter (float fCenter);
    float GetCenter ();
    void SetBandwidth (float fBandwidth);
    float GetBandwidth ();
    void SetCutoff (float fCutoff);
    float GetCutoff ();

    static const float MIN_GAIN;
    static const float MAX_GAIN;
    static const float MIN_INTENSITY;
    static const float MAX_INTENSITY;
    static const float MIN_CENTER;
    static const float MAX_CENTER;
    static const float MIN_BANDWIDTH;
    static const float MAX_BANDWIDTH;
    static const float MIN_CUTOFF;
    static const float MAX_CUTOFF;

protected:
    float m_fGain;
    float m_fIntensity;
    float m_fCenter;
    float m_fBandwidth;
    float m_fCutoff;
};

///////////////////////////////////////////////////////////////////////////////

class EnVerbEffect : public AudioEffect
{
public:
    EnVerbEffect ();

    static const long MIN_ROOMATTEN;
    static const long MAX_ROOMATTEN;
    static const long MIN_ROOMHFATTEN;
    static const long MAX_ROOMHFATTEN;
    static const long MIN_REFLECTATTEN;
    static const long MAX_REFLECTATTEN;
    static const long MIN_REVERBATTEN;
    static const long MAX_REVERBATTEN;
    static const float MIN_REFLECTDELAY;
    static const float MAX_REFLECTDELAY;
    static const float MIN_REVERBDELAY;
    static const float MAX_REVERBDELAY;
    static const float MIN_DECAYTIME;
    static const float MAX_DECAYTIME;
    static const float MIN_DECAYTIMEHFRATIO;
    static const float MAX_DECAYTIMEHFRATIO;
    static const float MIN_ROLLOFF;
    static const float MAX_ROLLOFF;
    static const float MIN_DIFFUSION;
    static const float MAX_DIFFUSION;
    static const float MIN_DENSITY;
    static const float MAX_DENSITY;
    static const float MIN_HFREF;
    static const float MAX_HFREF;

    enum PRESET
    {
        ALLEY = 0, 
        ARENA, 
                AUDITORIUM, 
        BATHROOM, 
        CARPETEDHALLWAY, 
        CAVE, 
        CITY,
        CONCERTHALL, 
        DEFAULT, 
        FOREST, 
        GENERIC, 
        HALLWAY, 
        HANGAR, 
        LARGEHALL, 
        LARGEROOM, 
        LIVINGROOM, 
        MEDIUMHALL, 
        MEDIUMROOM, 
        MOUNTAINS, 
        PADDEDCELL, 
        PARKINGLOT,
        PLAIN, 
        PLATE,        
        QUARRY, 
        ROOM, 
        SEWERPIPE, 
        SMALLROOM, 
        STONECORRIDOR, 
        STONEROOM, 
        UNDERWATER,
        NONE
    };

    enum QUALITY
    {
        MINIMUM,
        MEDIUM,
        MAXIMUM
    };

    void SetRoomAtten (long lAtten);
    long GetRoomAtten ();
    void SetRoomHFAtten (long lAtten);
    long GetRoomHFAtten ();
    void SetReflectAtten (long lAtten);
    long GetReflectAtten ();
    void SetReverbAtten (long lAtten);
    long GetReverbAtten ();
    void SetReflectDelay (float fDelay);
    float GetReflectDelay ();
    void SetReverbDelay (float fDelay);
    float GetReverbDelay ();
    void SetDecayTime (float fTime);
    float GetDecayTime (); 
    void SetDecayTimeHFRatio (float fRatio);
    float GetDecayTimeHFRatio ();
    void SetRolloff (float fRolloff);
    float GetRolloff ();
    void SetDiffusion (float fDiffusion);
    float GetDiffusion ();
    void SetDensity (float fDensity);
    float GetDensity ();
    void SetHFRef (float fRef);
    float GetHFRef ();
    void SetPreset (PRESET ePreset);
    PRESET GetPreset ();
    void SetQuality (QUALITY eQuality);
    QUALITY GetQuality ();
    bool& UpdateQuality ();

protected:
    long m_lRoomAtten;
    long m_lRoomHFAtten; 
    long m_lReflectAtten;
    long m_lReverbAtten;
    float m_fReflectDelay;
    float m_fReverbDelay; 
    float m_fDecayTime;
    float m_fDecayTimeHFRatio;
    float m_fRolloff;
    float m_fDiffusion;
    float m_fDensity;
    float m_fHFRef;
    PRESET m_ePreset;
    QUALITY m_eQuality;
    bool m_bUpdateQuality;
};

///////////////////////////////////////////////////////////////////////////////

class FlangerEffect : public AudioEffect
{
public:
    FlangerEffect ();

    enum WAVEFORM
    {
        SINE = 0,
        TRIANGLE
    };

    enum PHASE
    {
        NEG_180 = 0,
        NEG_90,
        ZERO,
        POS_90,
        POS_180
    };
    
    void SetMix (float fMix);
    float GetMix ();
    void SetFeedback (float fFeedback);
    float GetFeedback ();
    void SetDelay (float fDelay);
    float GetDelay ();
    void SetDepth (float fDepth);
    float GetDepth ();
    void SetFrequency (float fFrequency);
    float GetFrequency ();
    void SetWaveform (WAVEFORM eWaveform);
    WAVEFORM GetWaveform ();
    void SetPhase (PHASE ePhase);
    PHASE GetPhase ();

    static const float MAX_MIX;
    static const float MIN_MIX;
    static const float MIN_FEEDBACK;
    static const float MAX_FEEDBACK;
    static const float MIN_DELAY;
    static const float MAX_DELAY;
    static const float MIN_DEPTH;
    static const float MAX_DEPTH;
    static const float MIN_FREQ;
    static const float MAX_FREQ;

protected:
  float m_fMix;
  float m_fDepth;
  float m_fFeedback;
  float m_fFrequency;
  float m_fDelay;
  WAVEFORM m_eWaveform;
  PHASE m_ePhase;
};

///////////////////////////////////////////////////////////////////////////////

class ParametricEqEffect : public AudioEffect
{
public:
    ParametricEqEffect();

    void SetCenter (float fCenter);
    float GetCenter ();
    void SetBandwidth (float fBandwidth);
    float GetBandwidth ();
    void SetGain (float fGain);
    float GetGain ();

    static const float MIN_GAIN;
    static const float MAX_GAIN;
    static const float MIN_CENTER;
    static const float MAX_CENTER;
    static const float MIN_BANDWIDTH;
    static const float MAX_BANDWIDTH;

protected:
    float m_fCenter;
    float m_fBandwidth;
    float m_fGain;
};

///////////////////////////////////////////////////////////////////////////////

class ReverbEffect : public AudioEffect
{
public:
    ReverbEffect ();

    void SetInputGain (float fGain);
    float GetInputGain ();
    void SetMix (float fMix);
    float GetMix ();
    void SetTime (float fTime);
    float GetTime ();
    void SetHFRatio (float fRatio);
    float GetHFRatio ();
    
    static const float MIN_GAIN;
    static const float MAX_GAIN;
    static const float MIN_MIX;
    static const float MAX_MIX;
    static const float MIN_TIME;
    static const float MAX_TIME;
    static const float MIN_HFRATIO;
    static const float MAX_HFRATIO;

protected:
    float m_fInputGain;
    float m_fMix;
    float m_fTime;
    float m_fHFRatio;
};

#include "MAAudioEffects.inl"

} // namespace MagicAudio

#endif // _MAAUDIOEFFECTS_H