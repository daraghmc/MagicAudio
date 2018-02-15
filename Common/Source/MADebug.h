// MADebug.h - provides tracing for debug builds of applications.

#if !defined(_MADEBUG_H)
#define _MADEBUG_H

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <windows.h>

namespace MagicAudio
{
#if defined _DEBUG
// Convenience macros (should make MFC programmers feel at home), taking zero, one or two parameters

#define _TRACE0(MESSAGE) MindGames::_TRACE(MESSAGE)
#define _TRACE1(MESSAGE, PARAM) MindGames::_TRACE(MESSAGE, PARAM)
#define _TRACE2(MESSAGE, PARAM1, PARAM2) MindGames::_TRACE(MESSAGE, PARAM1, PARAM2)

// _TRACE() - Core trace routine, works like printf(), by specifying the string to
// output, including any conversion specifiers, followed by any arguments to be converted
// Maximum string length is 512 characters

static void _TRACE(const wchar_t* lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	wchar_t szBuffer[512];

	nBuf = _vsnwprintf(szBuffer, 512, lpszFormat, args); 
	
	OutputDebugString(szBuffer);
}

#else

// For Release builds, to prevent compiler errors...

static void _TRACE(const char *, ...){}

#define _TRACE0 {}
#define _TRACE1(MESSAGE, PARAM) {}
#define _TRACE2(MESSAGE, PARAM1, PARAM2) {}

#endif // defined(DEBUG)

}; // namespace MindGames

#endif // _MADEBUG_H