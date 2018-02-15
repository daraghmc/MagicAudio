#ifndef WAVTOMAFEXCEPTION_H
#define WAVTOMAFEXCEPTION_H

#include "MACommon.h"
using namespace MagicAudio;

#include "resource.h"

#define MAF_ERR(iResID) MA_THROW_ERR(WavToMafException, GetResString(iResID));

static inline TCHAR* GetResString (int iResId)
{
// NOTE: maximum resource string length is 512 characters!
    static TCHAR acBuff[512];
    return LoadString((HINSTANCE)GetModuleHandle(0),iResId,acBuff,sizeof(acBuff)) ? acBuff : NULL;
}

TCHAR* GetResString (int iResId);

// Class AudioException - video-specific exception class

class WavToMafException : public WindowedException
{
public:
    WavToMafException(wchar_t* acContext = NULL, int iCode = 0, wchar_t* acDescription = NULL, int iSeverity = SEV_FATAL) :
        WindowedException(acContext, iCode, acDescription, iSeverity)
    {
        SetName(L"WavToMaf Exception");
    }
};

#endif WAVTOMAFEXCEPTION_H