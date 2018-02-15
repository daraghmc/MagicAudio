#include "MAPanable.h"
#include "MAAudio.mcr"

using namespace MagicAudio;

const int Panable::LEFT = -100;
const int Panable::RIGHT = 100;

Panable::Panable ()
{
    m_iPan = 0;
}

void Panable::SetPan (int iPan)
{
    MAAUDIO_CLAMP(iPan,LEFT,RIGHT);
    m_iPan = iPan;
}
