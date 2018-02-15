#ifndef _MAWINDOWEDEXCEPTION_H
#define _MAWINDOWEDEXCEPTION_H

#include "MAException.h"

#include <windows.h>

namespace MagicAudio
{

class WindowedException : public Exception
{
public:
	WindowedException(
		wchar_t* acContext = NULL,
		int iCode = 0, 
		wchar_t* acDescription = NULL,
		int iSeverity = SEV_FATAL);

	virtual ~WindowedException(){};

	static void SetWindow(int iWindow);
	void Show();
	void Show(int iWindow);

protected:
	static int ms_iWindow;
};

} // namespace MagicAudio

#endif // _MAWINDOWEDEXCEPTION_H