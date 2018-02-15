#include "MASound3D.h"
#include "MAAudio.mcr"

using namespace MagicAudio;

///////////////////////////////////////////////////////////////////////////////

const int SoundCone::MIN_ANGLE = 0;
const int SoundCone::MAX_ANGLE = 360;

SoundCone::SoundCone ()
{
    m_kOrient = Vector3f::UNIT_X;
    m_iInsideAngle = MIN_ANGLE;
    m_iOutsideAngle = MAX_ANGLE;
    m_uiOutsideVol = Audio::MAX_VOL;
}

SoundCone& SoundCone::operator= (const SoundCone& rkCone)
{
    m_kOrient = rkCone.m_kOrient;
    m_iInsideAngle = rkCone.m_iInsideAngle;
    m_iOutsideAngle = rkCone.m_iOutsideAngle;
    m_uiOutsideVol = rkCone.m_uiOutsideVol;

    return *this;
}

void SoundCone::SetInsideAngle (int iAngle)
{
    MAAUDIO_CLAMP(iAngle,MIN_ANGLE,MAX_ANGLE);
    m_iInsideAngle = iAngle;
}

void SoundCone::SetOutsideAngle (int iAngle)
{
    MAAUDIO_CLAMP(iAngle,MIN_ANGLE,MAX_ANGLE);
    m_iOutsideAngle = iAngle;
}

void SoundCone::SetOutsideVol (unsigned int uiVol)
{
    MAAUDIO_CLAMP(uiVol,Audio::MIN_VOL,Audio::MAX_VOL);
    m_uiOutsideVol = uiVol;
}

///////////////////////////////////////////////////////////////////////////////

const float Sound3D::MAX_VOLDIST = 1E9f;
const float Sound3D::MIN_VOLDIST = 1.0f;

Sound3D::Sound3D ()
{
    m_kPosition = Vector3f::ZERO;
    m_kVelocity = Vector3f::ZERO;
    m_fMaxVolDist = MAX_VOLDIST;
    m_fMinVolDist = MIN_VOLDIST;
    m_eMode = MODE_ABSOLUTE;
}

void Sound3D::SetMinVolDist (float fDist)
{
    MAAUDIO_CLAMP(fDist,MIN_VOLDIST,MAX_VOLDIST);
    m_fMinVolDist = fDist;
}

void Sound3D::SetMaxVolDist (float fDist)
{
    MAAUDIO_CLAMP(fDist,MIN_VOLDIST,MAX_VOLDIST);
    m_fMaxVolDist = fDist;
}

///////////////////////////////////////////////////////////////////////////////

const float Listener3D::MIN_ROLLOFF = 0.0f; 
const float Listener3D::MAX_ROLLOFF = 10.0f; 
const float Listener3D::MIN_DOPPLER = 0.0f;
const float Listener3D::MAX_DOPPLER = 10.0f;
const float Listener3D::MIN_DISTSCALE = FLT_MIN;
const float Listener3D::MAX_DISTSCALE = FLT_MAX;

Listener3D::Listener3D ()
{
    m_kPosition = Vector3f::ZERO;
    m_kVelocity = Vector3f::ZERO;
    m_kFront = Vector3f::UNIT_Z;
    m_kTop = Vector3f::UNIT_Y;
    m_fDoppler = 1.0f;
    m_fRolloff = 1.0f;
    m_fDistanceScale = 1.0f;
}

void Listener3D::SetDoppler (float fDoppler)
{
    MAAUDIO_CLAMP(fDoppler,MIN_DOPPLER,MAX_DOPPLER);
    m_fDoppler = fDoppler;
}

void Listener3D::SetRolloff (float fRolloff)
{
    MAAUDIO_CLAMP(fRolloff,MIN_ROLLOFF,MAX_ROLLOFF);
    m_fRolloff = fRolloff;
}

void Listener3D::SetDistanceScale (float fScale)
{
    MAAUDIO_CLAMP(fScale,MIN_DISTSCALE,MAX_DISTSCALE);
    m_fDistanceScale = fScale;
}
