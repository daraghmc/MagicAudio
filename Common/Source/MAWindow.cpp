// Window.cpp - Implementation of class Window.
// See Window.h for details

#include "MAWindow.h"
#include "MAGlobalPtrCache.h"

namespace MagicAudio
{

// Global Window pointer cache. An instance of Window stores its "this" pointer here, on
// a temporary basis, until the thunk has been performed
//CGlobalPtrCache<MindGames::Window> g_WindowPtrCache;

CGlobalPtrCache<MagicAudio::Window>& GetWindowPtrCache()
{
	static CGlobalPtrCache<MagicAudio::Window> s_WindowPtrCache;
	return s_WindowPtrCache;
}


///////////////////////////////////////
// Window - public method implementations
///////////////////////////////////////

// Create() - Register a new (generic) window class, and cache the "this" pointer
// [returns] BOOL, TRUE if creation is successful, FALSE otherwise
 
BOOL Window::Create(DWORD dwStyle, int x, int y,
					 int nWidth, int nHeight, HWND hWndParent,
					 wchar_t* szWindowName, wchar_t* szClassName)
{
// Register the window class
	if( !Register(szClassName) ) return FALSE;
// Cache the "this" pointer
	GetWindowPtrCache().SetPtr(this);
// Create the window, and store its HWND
	m_hWnd = CreateWindow(MAKEINTATOM(m_wndClassAtom),
						  szWindowName,
						  dwStyle,
						  x, y, nWidth, nHeight,
						  hWndParent,
						  NULL,
						  (HINSTANCE)GetModuleHandle(0),
						  NULL); 

	return (m_hWnd != NULL);
}

//////////////////////////////////////////////////////////////
// Window - protected method implementations
//////////////////////////////////////////////////////////////


// Register() - Register a generic window class

BOOL Window::Register(wchar_t* szClassName)
{	
// Synthetic window class naming
	if(szClassName == NULL){ 
		m_szClassName = new wchar_t[32];
		if( m_szClassName == NULL ) return FALSE;
		wsprintf(m_szClassName, L"MagicAudioWINDOW:%8.8X", (DWORD)this);
	}
	else{
		m_szClassName = new wchar_t[wcslen(szClassName) + 1];
		if( m_szClassName == NULL ) return FALSE;
		wcscpy(m_szClassName, szClassName);
	}

	WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
	HINSTANCE hInst = (HINSTANCE)GetModuleHandle(0);

	wc.style = CS_OWNDC;
	wc.lpfnWndProc = StartWindowProc; // Startup WindowProc, before the thunk
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = 0;
	wc.hCursor = 0;
	wc.hbrBackground = HBRUSH(COLOR_WINDOW + 1);
	wc.lpszMenuName = 0;
	wc.lpszClassName = m_szClassName;	// window class name
// Do the registration
	return( m_wndClassAtom = ::RegisterClass(&wc) );
}

// StartWindowProc() - Startup WindowProc, which performs the thunk

LRESULT CALLBACK Window::StartWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
// Retrieve our instance pointer from global storage
	Window *pThis;
	GetWindowPtrCache().GetPtr(&pThis);
// Save hwnd in class, before we thunk it to an instance pointer
	pThis->m_hWnd = hWnd;
// Initialise the thunk, using the address of ActualWindowProc as the new WindowProc
	pThis->m_thunk.Init(pThis->GetWindowProc(), pThis);
// Cast the pointer to ActualWindowProc() to a WNDPROC pointer
	WNDPROC pProc = (WNDPROC)&(pThis->m_thunk.thunk);
// Set the class's window procedure to ActualWindowProc() - note that, after the thunk,
// ActualWindowProc() will receive an instance pointer as its HWND parameter
	::SetWindowLong(hWnd, GWL_WNDPROC, (LONG)pProc);
	return pProc(hWnd, uMsg, wParam, lParam);
}

} // namespace MagicAudio


