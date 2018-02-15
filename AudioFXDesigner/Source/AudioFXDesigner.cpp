#include "stdafx.h"
#include "AudioFXDesigner.h"
#include "AudioFXDesignerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CAudioFXDesignerApp, CWinApp)
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CAudioFXDesignerApp::CAudioFXDesignerApp()
{
    m_pkDlg = NULL;
}

CAudioFXDesignerApp theApp;

BOOL CAudioFXDesignerApp::InitInstance()
{
    InitCommonControls();
    CWinApp::InitInstance();
    m_pkDlg = new CAudioFXDesignerDlg;
    m_pMainWnd = m_pkDlg;
    m_pkDlg->Create(IDD_AUDIOFXDESIGNER,NULL);
    return TRUE;
}

BOOL CAudioFXDesignerApp::OnIdle(LONG lCount)
{
    if (CWinApp::OnIdle(lCount))
        return TRUE;
        
    if ( m_pkDlg != NULL )
        m_pkDlg->OnIdle();
        
    return TRUE;
}

int CAudioFXDesignerApp::ExitInstance()
{
    if ( m_pkDlg != NULL )
        delete m_pkDlg;

    return CWinApp::ExitInstance();
}
