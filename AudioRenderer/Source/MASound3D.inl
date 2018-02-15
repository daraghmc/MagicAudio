inline void SoundCone::SetOrientation (const Vector3f& rkOrient)  
{ 
    m_kOrient = rkOrient; 
}

inline Vector3f& SoundCone::GetOrientation ()  
{ 
    return m_kOrient; 
}

inline int SoundCone::GetInsideAngle ()
{
    return m_iInsideAngle;
}

inline int SoundCone::GetOutsideAngle ()
{
    return m_iOutsideAngle;
}

inline unsigned int SoundCone::GetOutsideVol ()
{
    return m_uiOutsideVol;
}

///////////////////////////////////////////////////////////////////////////////

inline void Audio3D::SetPosition (const Vector3f& rkPosition)
{
    m_kPosition = rkPosition;
}

inline Vector3f& Audio3D::GetPosition ()
{
    return m_kPosition;
}

inline void Audio3D::SetVelocity (const Vector3f& rkVelocity)
{
    m_kVelocity = rkVelocity;
}

inline Vector3f& Audio3D::GetVelocity ()
{
    return m_kVelocity;
}

inline void Sound3D::SetCone (SoundCone& rkCone)
{
    m_kCone = rkCone;
}

inline SoundCone& Sound3D::GetCone ()
{ 
    return m_kCone;
}

inline float Sound3D::GetMinVolDist ()
{
    return m_fMinVolDist;
}

inline float Sound3D::GetMaxVolDist ()
{
    return m_fMaxVolDist;
}

inline void Sound3D::SetMode (Sound3D::MODE eMode)
{
    m_eMode = eMode;
}

inline Sound3D::MODE Sound3D::GetMode ()
{
    return m_eMode;
}

///////////////////////////////////////////////////////////////////////////////

inline void Listener3D::SetFront (const Vector3f& rkFront)
{
    m_kFront = rkFront;
}

inline Vector3f& Listener3D::GetFront ()
{
    return m_kFront;
}

inline void Listener3D::SetTop (const Vector3f& rkTop)
{
    m_kTop = rkTop;
}

inline Vector3f& Listener3D::GetTop ()
{
    return m_kTop;
}

inline float Listener3D::GetDoppler ()
{
    return m_fDoppler;
}

inline float Listener3D::GetRolloff ()
{
    return m_fRolloff;
}

inline float Listener3D::GetDistanceScale ()
{
    return m_fDistanceScale;
}
