#pragma once

#ifndef _WINDOW_H
#define _WINDOW_H

#include <windows.h>
#include "MADebug.h"
#include "MASynchronization.h"

using namespace MagicAudio;

///////////////////////////////////////
// WndProcThunk - struct declaration
///////////////////////////////////////

// Thunk to convert the HWND of the window to the "this" pointer of a Window object,
// thereby allowing a per-instance WindowProc to be called

#pragma pack(push, 1)
struct _WndProcThunk
{
	DWORD m_mov;		// move instruction
	DWORD m_this;		// pointer to instance
	BYTE m_jmp;			// jump instruction
	DWORD m_relproc;	// how far to jump
};
#pragma pack(pop)

///////////////////////////////////////
// Window - class definition
///////////////////////////////////////

// Simple wrapper for _WndProcThunk structure, to initialize the thunk on a
// per-instance basis

class CWndProcThunk
{
public:
	_WndProcThunk thunk;
	
	void Init(WNDPROC proc, void* pThis)
	{
// Intelspeak for "mov esp+4" - the HWND parameter of WindowProc is stored after the return
// address, at esp+4. We are going to thunk this parameter to an instance of Window
		thunk.m_mov = 0x042444c7;
// Operand for the mov (pointer to instance of Window) 
		thunk.m_this = (DWORD)pThis;
// Intelspeak for "jmp"
		thunk.m_jmp = 0xe9;	
// Operand for jmp (relative offset to instance's ActualWindowProc() member)
		thunk.m_relproc = (int)proc - ((int)this + sizeof(_WndProcThunk));
	}
};

namespace MagicAudio
{
///////////////////////////////////////
// Window - class declaration
///////////////////////////////////////

// Wrapper for a message sink window
class Window
{
public:
	ATOM m_wndClassAtom;	// Window class identifier
	HWND m_hWnd;			// HWND of underlying window
	CWndProcThunk m_thunk;  // Thunk to allow per-instance WindowProc
	wchar_t* m_szClassName;   // Window class name

protected:
// Register a new (generic) window class
	BOOL Register(wchar_t* szClassName);
// WindowProc used to get the ball rolling
	static LRESULT CALLBACK StartWindowProc(HWND, UINT, WPARAM, LPARAM);
// WindowProc that is called after the thunk
	static LRESULT CALLBACK ActualWindowProc(HWND, UINT, WPARAM, LPARAM);
// Gets the address of ActualWindowProc()
	WNDPROC GetWindowProc(){ return ActualWindowProc; };
// Overridable per-instance WindowProc
	virtual LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
// Constructor
	Window();
// Destructor
	virtual ~Window();
// Register window class and create window
	BOOL Create(DWORD dwStyle = WS_OVERLAPPED, 
				int x = 0,int y = 0, int nWidth = 0, int nHeight = 0, 
				HWND hWndParent = NULL,
				wchar_t* szWindowName = NULL, wchar_t* szClassName = NULL);
// Get the HWND of the underlying window
	HWND GetHWND();
};

} // namespace MagicAudio

//////////////////////////////////////////////////////////////
// Window - Inline methods
//////////////////////////////////////////////////////////////

// Window() - Constructor

inline MagicAudio::Window::Window() : m_wndClassAtom(0), m_hWnd(0), m_szClassName(NULL) {}

// ~Window() - Destructor

inline MagicAudio::Window::~Window()
{
	if(::IsWindow(m_hWnd))
		DestroyWindow(m_hWnd);

	if( m_wndClassAtom != 0 )
		UnregisterClass(m_szClassName, GetModuleHandle(0));

	if( m_szClassName != NULL ) delete [] m_szClassName;
}

// ActualWindowProc() - WindowProc that is used after window creation to route messages to
// per-instance WindowProc(). After the thunk, the HWND parameter has been set to the instance's
// "this" pointer

inline LRESULT CALLBACK MagicAudio::Window::ActualWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
// Cast the hWnd
	Window *pThis = (Window *)hWnd;
	LRESULT lResult = pThis->WindowProc(pThis->m_hWnd, uMsg, wParam, lParam);
// If the per-instance WindowProc() didn't handle the message then call default window procedure
	if( lResult == 0 ){
		switch( uMsg )
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return TRUE;
		default:
			return ::DefWindowProc(pThis->m_hWnd, uMsg, wParam, lParam);
		}
	}
		
	return lResult;
}

// GetHWND() - Return the window handle of this window

inline HWND MagicAudio::Window::GetHWND()
{
	_ASSERTE(::IsWindow(m_hWnd));
	return m_hWnd;
}

inline 	LRESULT MagicAudio::Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}


#endif // _WINDOW_H
