#include "MAWindowedException.h"
#include <stdio.h>

namespace MagicAudio
{

int WindowedException::ms_iWindow = NULL;

WindowedException::WindowedException(wchar_t* acContext, int iCode, wchar_t* acDescription, int iSeverity) :
	Exception(acContext, iCode, acDescription, iSeverity)	
{
}

void WindowedException::SetWindow(int iWindow)
{
	ms_iWindow = iWindow;
}

void WindowedException::Show(int iWindow)
{
	MakeErrorMessage();

	if( iWindow == 0 )
		OutputDebugString(m_acErrorMessage);
	else{
		UINT uiType;
		switch( m_iSeverity )
		{
		case SEV_WARN:
			uiType = MB_OK || MB_ICONEXCLAMATION;
			break;
		case SEV_FATAL:
			uiType = MB_OK || MB_ICONSTOP;
			break;
		default:
			uiType = MB_OK || MB_ICONSTOP;

		}
		::MessageBox((HWND)iWindow, m_acErrorMessage, m_acName, uiType);
	}
}

void WindowedException::Show()
{
	Show(ms_iWindow);
}

} // namespace MagicAudio

