#ifndef _MAPANABLE_H
#define _MAPANABLE_H

#include "MAAudio.h"

namespace MagicAudio
{

class Panable : public Audio
{
public:
    Panable ();
    virtual void SetPan (int iPan);
    virtual int GetPan ();

    static const int LEFT;
    static const int RIGHT;

protected:
    int m_iPan;
};

#include "MAPanable.inl"

} // namespace MagicAudio

#endif // _MAPANABLE_H