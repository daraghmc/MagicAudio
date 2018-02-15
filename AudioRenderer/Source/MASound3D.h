#ifndef _MASOUND3D_H
#define _MASOUND3D_H

#include "MAAudio.h"
#include "MAVector3.h"

namespace MagicAudio
{
class SoundCone
{
public:
    SoundCone ();
    
    SoundCone& operator= (const SoundCone& rkCone);
    void SetOrientation (const Vector3f& rkOrient);
    Vector3f& GetOrientation ();
    void SetInsideAngle (int iAngle);
    int GetInsideAngle ();
    void SetOutsideAngle (int iAngle);
    int GetOutsideAngle ();
    void SetOutsideVol (unsigned int uiVol);
    unsigned int GetOutsideVol ();

    static const int MIN_ANGLE;
    static const int MAX_ANGLE;

protected:
    Vector3f m_kOrient;
    int m_iInsideAngle;
    int m_iOutsideAngle;
    unsigned int m_uiOutsideVol;  
};


///////////////////////////////////////////////////////////////////////////////

class Audio3D : public Audio
{
public:
    void SetPosition (const Vector3f& rkPosition);
    Vector3f& GetPosition ();
    void SetVelocity (const Vector3f& rkVelocity);
    Vector3f& GetVelocity ();

protected:
    Vector3f m_kPosition;
    Vector3f m_kVelocity;
};

///////////////////////////////////////////////////////////////////////////////

class Sound3D : public Audio3D
{
public:
    Sound3D ();

    enum MODE
    {
        MODE_ABSOLUTE = 0,
        MODE_HEAD,
        MODE_DISABLED
    };
 
    static const float MIN_VOLDIST;
    static const float MAX_VOLDIST;

    void SetCone (SoundCone& rkCone);
    SoundCone& GetCone ();
    void SetMaxVolDist (float fDist);
    float GetMaxVolDist ();
    void SetMinVolDist (float fDist);
    float GetMinVolDist ();
    void SetMode (MODE eMode);
    MODE GetMode ();
    
protected:
    float m_fMaxVolDist;
    float m_fMinVolDist;
    SoundCone m_kCone;
    MODE m_eMode;
};

///////////////////////////////////////////////////////////////////////////////

class Listener3D : public Audio3D
{
public:
    Listener3D ();

    void SetTop (const Vector3f& kTop);
    Vector3f& GetTop ();
    void SetFront (const Vector3f& kFront);
    Vector3f& GetFront ();
    void SetDoppler (float fDoppler);
    float GetDoppler (); 
    void SetRolloff (float fRolloff);
    float GetRolloff ();
    void SetDistanceScale (float fScale);
    float GetDistanceScale ();

    static const float MIN_ROLLOFF; 
    static const float MAX_ROLLOFF; 
    static const float MIN_DOPPLER;
    static const float MAX_DOPPLER;
    static const float MIN_DISTSCALE;
    static const float MAX_DISTSCALE;
 
protected:
    Vector3f m_kTop;
    Vector3f m_kFront;
    float m_fDoppler;
    float m_fRolloff;    
    float m_fDistanceScale;
};

#include "MASound3D.inl"

} // namespace MindGames

#endif // MGSOUND3D_H