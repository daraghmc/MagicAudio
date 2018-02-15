#include "WavToMafDialog.h"
#include "WavToMafException.h"
#include "resource.h"
#include "MafMaker.h"
#include <shlobj.h>

WavToMafDialog::WavToMafDialog()
{
    m_hConvertThread = NULL;
    m_kThreadParams.hKillEvent = CreateEvent(NULL,NULL,FALSE,NULL);
    m_kThreadParams.pkFileInfo = &m_kFileInfo;
}

WavToMafDialog::~WavToMafDialog()
{
    if ( m_kThreadParams.hKillEvent != NULL )
        CloseHandle(m_kThreadParams.hKillEvent);

    if ( m_hConvertThread != NULL )
        CloseHandle(m_hConvertThread);
}

void WavToMafDialog::Show ()
{
    if ( DialogBoxParam((HINSTANCE)GetModuleHandle(0),MAKEINTRESOURCE(IDD_MAIN),NULL,
        MessageProc,(LPARAM)this) ==  -1 )
    {
        MAF_ERR(IDS_ERR_SHOWDIALOG);
    }
}

INT_PTR CALLBACK WavToMafDialog::MessageProc (HWND hWnd, UINT uMsg, WPARAM wParam, 
    LPARAM lParam)
{
    static WavToMafDialog* pkDialog;

    switch ( uMsg )
    {
    case WM_INITDIALOG:
        pkDialog = (WavToMafDialog*)lParam;
        pkDialog->OnInitDialog(hWnd);
        return FALSE;
    
    case WM_COMMAND:
        switch ( LOWORD(wParam) ) 
        {
        case IDOK:
            EndDialog(hWnd,1);
            return TRUE;
        case IDCANCEL:
            pkDialog->OnCancel(hWnd);
            return TRUE;
        case IDC_BUTTON_FILES:
            pkDialog->OnSelectFiles(hWnd);
            return TRUE;
        case IDC_BUTTON_CONVERT:
            pkDialog->OnConvert(hWnd);
            return TRUE;
        case IDC_BUTTON_FOLDER:
            pkDialog->OnBrowse(hWnd);
            return TRUE;
        }

    case WAVTOMAF_MSG_PROGRESS:
        pkDialog->OnProgress(hWnd,(int)wParam);
        return TRUE;

    case WAVTOMAF_MSG_DONE:
        pkDialog->OnDone(hWnd);
        return TRUE;

    case WM_CLOSE:
        pkDialog->OnClose(hWnd);
        EndDialog(hWnd, 0);
        return TRUE;
    }

    return FALSE;
}

void WavToMafDialog::OnInitDialog (HWND hWnd)
{
    HWND hWndDeskTop = GetDesktopWindow();
    if ( hWndDeskTop != NULL )
    {
        RECT kDeskRect, kAppRect;
        GetClientRect(hWndDeskTop,&kDeskRect);
        GetWindowRect(hWnd,&kAppRect);
        int iLeft = (kDeskRect.right - kDeskRect.left) / 2 -
            (kAppRect.right - kAppRect.left) / 2;
        int iTop = (kDeskRect.bottom - kDeskRect.top) / 2 -
            (kAppRect.bottom - kAppRect.top) / 2;
        SetWindowPos(hWnd,0,iLeft,iTop,0,0,SWP_NOSIZE | SWP_NOZORDER);
    }

    EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_CONVERT),FALSE);
    EnableWindow(GetDlgItem(hWnd,IDCANCEL),FALSE);

    HWND hWndProg = GetDlgItem(hWnd,IDC_PROGRESS_CONVERT);
    SendMessage(hWndProg,PBM_SETRANGE,0,MAKELPARAM(0,WAVTOMAF_PROGRESSSCALE)); 
    SendMessage(hWndProg,PBM_SETSTEP,(WPARAM)1,0);

    HANDLE hBitmap = LoadImage((HINSTANCE)GetModuleHandle(0),
        MAKEINTRESOURCE(IDB_FOLDER),IMAGE_BITMAP,0,0,0);

    HWND hWndButton = GetDlgItem(hWnd,IDC_BUTTON_FOLDER);
    SendMessage(hWndButton,BM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hBitmap);
    m_kThreadParams.hNotifyWnd = hWnd;
}

void WavToMafDialog::OnSelectFiles (HWND hWnd)
{
    wchar_t acFiles[_MAX_PATH + MAXFILES * _MAX_FNAME];
    *acFiles = '\0';
    m_kFileInfo.kFiles.clear();

    OPENFILENAME kOFN;
    memset(&kOFN,0,sizeof(OPENFILENAME));
    kOFN.lStructSize = sizeof(OPENFILENAME);
    kOFN.hwndOwner = hWnd;
    kOFN.lpstrFile = acFiles;
    kOFN.lpstrFilter = L"Wave Files\0*.wav\0";
    kOFN.Flags = OFN_ALLOWMULTISELECT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | 
        OFN_LONGNAMES | OFN_EXPLORER;
    kOFN.lpstrTitle = GetResString(IDS_TITLE_SELECTFILES);
    kOFN.nMaxFile = _MAX_PATH + MAXFILES * _MAX_FNAME;
    
    if ( ::GetOpenFileName(&kOFN) != TRUE )
    {
        EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_CONVERT),FALSE);
        return;
    }

    wstring strFullPath(acFiles);
    wchar_t* pacNext = acFiles + wcslen(acFiles) + 1;

    if ( strFullPath.find('.') != string::npos )
    {
        int iPos = strFullPath.rfind('\\');
        if ( iPos != string::npos )
        {
            wstring strFileName = strFullPath.substr(iPos+1);
            m_kFileInfo.kFiles.push_back(strFileName);
            m_kFileInfo.strInputPath = strFullPath.substr(0,iPos);
            if ( m_kFileInfo.strOutputPath.empty() )
            {
                m_kFileInfo.strOutputPath = m_kFileInfo.strInputPath;
                SetDlgItemText(hWnd,IDC_STATIC_OUTPUTFOLDER,m_kFileInfo.strOutputPath.c_str());        
            }
        }
    }
    else
    {
        m_kFileInfo.strInputPath = strFullPath;
        if ( m_kFileInfo.strOutputPath.empty() )
        {
            m_kFileInfo.strOutputPath = m_kFileInfo.strInputPath;
            SetDlgItemText(hWnd,IDC_STATIC_OUTPUTFOLDER,m_kFileInfo.strOutputPath.c_str());
        }
    
        wstring strNext;
        do
        {
            strNext = pacNext;
            m_kFileInfo.kFiles.push_back(strNext);
            pacNext += wcslen(pacNext) + 1;
        }
        while ( *pacNext != L'\0' ); 
    }
    EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_CONVERT),TRUE);
}

void WavToMafDialog::OnConvert (HWND hWnd)
{
    EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_CONVERT),FALSE);
    EnableWindow(GetDlgItem(hWnd,IDOK),FALSE);
    EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_FILES),FALSE);
    EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_FOLDER),FALSE);
    EnableWindow(GetDlgItem(hWnd,IDCANCEL),TRUE);


    if ( m_hConvertThread != NULL )
        CloseHandle(m_hConvertThread);
    m_hConvertThread = CreateThread(NULL,0,ConvertThreadProc,(LPVOID)&m_kThreadParams,0,NULL);
    
    if ( m_hConvertThread == NULL )
        MAF_ERR(IDS_ERR_LAUNCHTHREAD);
}

void WavToMafDialog::OnProgress (HWND hWnd, int iCurrentProgress)
{
    HWND hWndProg = GetDlgItem(hWnd,IDC_PROGRESS_CONVERT);
    SendMessage(hWndProg,PBM_SETPOS,iCurrentProgress,0);
}

void WavToMafDialog::OnBrowse (HWND hWnd)
{
    wchar_t acPath[MAX_PATH];

    BROWSEINFO kInfo;
    kInfo.hwndOwner = hWnd;
    kInfo.lpszTitle = GetResString(IDS_TITLE_OUTPUTFOLDER);
    kInfo.lpfn = NULL;
    kInfo.pszDisplayName = acPath;
    kInfo.pidlRoot = NULL;
    kInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    kInfo.lParam = 0;
    kInfo.iImage = 0;

    LPITEMIDLIST pkList = SHBrowseForFolder(&kInfo);

    if ( pkList == NULL )
        return;

    if ( !SHGetPathFromIDList(pkList, acPath) )
        return;

    IMalloc* pqMalloc = NULL;
    if ( SUCCEEDED(SHGetMalloc(&pqMalloc)) ) 
    {
        pqMalloc->Free((void*)pkList);
        pqMalloc->Release();
    }

    m_kFileInfo.strOutputPath = acPath;
    SetDlgItemText(hWnd,IDC_STATIC_OUTPUTFOLDER,acPath);
}

void WavToMafDialog::OnCancel(HWND hWnd)
{
    if ( WaitForSingleObject(m_hConvertThread,0) == WAIT_TIMEOUT )
    {
        EnableWindow(GetDlgItem(hWnd,IDCANCEL),FALSE);
        EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_FILES),FALSE);
        EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_FOLDER),FALSE);
        EnableWindow(GetDlgItem(hWnd,IDOK),FALSE);
        EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_CONVERT),FALSE);
        SetEvent(m_kThreadParams.hKillEvent);    
    }
}

void WavToMafDialog::OnDone(HWND hWnd)
{
    EnableWindow(GetDlgItem(hWnd,IDCANCEL),FALSE);
    EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_FILES),TRUE);
    EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_FOLDER),TRUE);
    EnableWindow(GetDlgItem(hWnd,IDOK),TRUE);
    EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_CONVERT),TRUE);   
}

void WavToMafDialog::OnClose(HWND hWnd)
{
    EnableWindow(GetDlgItem(hWnd,IDCANCEL),FALSE);
    SetEvent(m_kThreadParams.hKillEvent);
    WaitForSingleObject(m_hConvertThread,INFINITE);
}

DWORD WINAPI WavToMafDialog::ConvertThreadProc(LPVOID pvParam)
{
    ThreadParams* pkParams = (ThreadParams*)pvParam;
    vector<wstring> kFiles = pkParams->pkFileInfo->kFiles;

    HWND hWndProg = GetDlgItem(pkParams->hNotifyWnd,IDC_PROGRESS_CONVERT);

    for (int i = 0; i < (int)kFiles.size(); i++)
    {
        if ( WaitForSingleObject(pkParams->hKillEvent,0) == WAIT_OBJECT_0 )
            break;
    
        SendMessage(hWndProg,PBM_SETPOS,0,0);
        SetDlgItemText(pkParams->hNotifyWnd, IDC_STATIC_CURRENTFILE, kFiles[i].c_str());
    
        MafMaker kMM(pkParams->hNotifyWnd);
        try
        {
            kMM.Convert(pkParams->pkFileInfo->strInputPath, pkParams->pkFileInfo->strOutputPath,kFiles[i]);
        }
        catch ( WavToMafException* pkEx )
        {
            wstring strDesc = pkEx->GetDescription();
            strDesc += L":\n";
            strDesc += kFiles[i];
            pkEx->SetDescription((wchar_t*)strDesc.c_str());
            pkEx->Show();
            delete pkEx;
        }
        Sleep(200);
    }

    PostMessage(pkParams->hNotifyWnd,WAVTOMAF_MSG_DONE,0,0);
    return TRUE;
}