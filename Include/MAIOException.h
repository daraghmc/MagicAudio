
#ifndef _MAIOEXCEPTION_H
#define _MAIOEXCEPTION_H

#include "MAWindowedException.h"

// Class IOException - Input output specific exception class

#define MA_IOERR_MSG(acMsg) MA_THROW_ERR(IOException, acMsg)
#define MA_IOWARN_MSG(acMsg) MA_THROW_WARN(IOException, acMsg)

namespace MagicAudio
{

class IOException : public WindowedException
{
public:
	IOException(wchar_t* acContext = NULL, int iCode = 0, wchar_t* acDescription = NULL,
        int iSeverity = SEV_FATAL);
};

} // namespace MagicAudio

#endif // _MAIOEXCEPTION_H
