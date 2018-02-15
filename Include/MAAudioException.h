#ifndef _MAAUDIOEXCEPTION_H
#define _MAAUDIOEXCEPTION_H

#include "MAWindowedException.h"

namespace MagicAudio
{
// Class AudioException - audio-specific exception class

class AudioException : public MagicAudio::WindowedException
{
public:
    AudioException(wchar_t* acContext = NULL, int iCode = 0, 
        wchar_t* acDescription = NULL, int iSeverity = SEV_FATAL);
};

} // namespace MagicAudio;

#endif // _MAAUDIOEXCEPTION_H
