// Magic Software, Inc.
// http://www.magic-software.com
// Copyright (c) 2000-2002.  All Rights Reserved
//
// Source code from Magic Software is supplied under the terms of a license
// agreement and may not be copied or disclosed except in accordance with the
// terms of that agreement.  The various license agreements may be found at
// the Magic Software web site.  This file is subject to the license
//
// 3D GAME ENGINE SOURCE CODE
// http://www.magic-software.com/License/3DGameEngine.pdf

#ifndef WAVTOMAFDIALOG_H
#define WAVTOMAFDIALOG_H

#include <windows.h>
#include <commctrl.h>
#include <string>
#include <vector>
using namespace std;

#define MAXFILES 100

class WavToMafDialog
{
public:
    WavToMafDialog();
    ~WavToMafDialog();

    void Show ();

private:
    static INT_PTR CALLBACK MessageProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static DWORD WINAPI ConvertThreadProc(LPVOID pvParam);

    void OnInitDialog (HWND hWnd);
    void OnSelectFiles (HWND hWnd);
    void OnConvert (HWND hWnd);
    void OnProgress (HWND hWnd, int iCurrentProgress);
    void OnBrowse (HWND hWnd);
    void OnCancel(HWND hWnd);
    void OnDone(HWND hWnd);
    void OnClose(HWND hWnd);

private:
    class FileInfo
    {
    public:
        wstring strInputPath;
        wstring strOutputPath;
        vector<wstring> kFiles;
    };

    class ThreadParams
    {
    public:
        HWND hNotifyWnd;
        HANDLE hKillEvent;       
        FileInfo* pkFileInfo;       
    };

private:
    ThreadParams m_kThreadParams;
    FileInfo m_kFileInfo;
    HANDLE m_hConvertThread;
};

#endif // #define WAVTOMAFDIALOG_H