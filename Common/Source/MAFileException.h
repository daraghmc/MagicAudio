#ifndef _MAFILEEXCEPTION_H
#define _MAFILEEXCEPTION_H

#include "MAWindowedException.h"

namespace MagicAudio
{

#define FILEERR_OPEN "Failed to open file"
#define FILEERR_READ "Failed to read from file"
#define FILEERR_WRITE "Failed to write to file"
#define FILEERR_CREATEDIR "Failed to create directory"

#define FILE_ERR(acFile, acError)\
    {\
    char acDescription[512];\
    strcpy(acDescription, acFile);\
    strcat(acDescription, "\n");\
    strcat(acDescription, acError);\
    MA_THROW_ERR(FileException, acDescription)\
    }\

class FileException : public WindowedException
{
public:
	FileException(wchar_t *acContext = NULL, int iCode = 0, wchar_t *acDescription = NULL, int iSeverity = SEV_FATAL) :
		WindowedException(acContext, iCode, acDescription, iSeverity)
	{
		SetName(L"File Exception");
	}
};

} // namespace MagicAudio

#endif // #define MAFILEEXCEPTION_H