#include "MAAudioException.h"
using namespace MagicAudio;

AudioException::AudioException (wchar_t* acContext, int iCode, wchar_t* acDescription, int iSeverity) :
    WindowedException(acContext,iCode,acDescription,iSeverity)
{
    SetName(L"Audio Exception");
}