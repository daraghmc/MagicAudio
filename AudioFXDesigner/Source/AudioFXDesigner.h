#pragma once

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CAudioFXDesignerDlg;

class CAudioFXDesignerApp : public CWinApp
{
public:
    CAudioFXDesignerApp();

protected:
    CAudioFXDesignerDlg* m_pkDlg;
    DECLARE_MESSAGE_MAP()
    virtual BOOL OnIdle(LONG lCount);
    virtual int ExitInstance();
    virtual BOOL InitInstance();
};

extern CAudioFXDesignerApp theApp;