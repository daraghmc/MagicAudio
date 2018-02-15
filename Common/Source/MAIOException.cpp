#include "MAIOException.h"

namespace MagicAudio
{

IOException::IOException (wchar_t* acContext, int iCode, wchar_t* acDescription, 
    int iSeverity) :
    WindowedException(acContext, iCode, acDescription, iSeverity)
{
	SetName(L"IO Exception");
}

} // namespace MagicAudio