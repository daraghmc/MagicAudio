#include "stdafx.h"
#include "AudioFXDesigner.h"
#include "EnVerbPropertyPage.h"

using namespace MagicAudio;

IMPLEMENT_DYNAMIC(CEnVerbPropertyPage, CPropertyPage)
CEnVerbPropertyPage::CEnVerbPropertyPage()
    : CPropertyPage(CEnVerbPropertyPage::IDD)
{
}

CEnVerbPropertyPage::~CEnVerbPropertyPage()
{
}

void CEnVerbPropertyPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_ENVERB_PRESETS, m_kPresetCombo);
    DDX_Control(pDX, IDC_CHECK_ENVERB_USEPRESET, m_kCheckUsePreset);
    DDX_Control(pDX, IDC_STATIC_ENVERB_ROOMATTEN, m_kRoomAttenDisplay);
    DDX_Control(pDX, IDC_STATIC_ENVERB_HFATTEN, m_kHFAttenDisplay);
    DDX_Control(pDX, IDC_STATIC_ENVERB_REFLECTATTEN, m_kReflectAttenDisplay);
    DDX_Control(pDX, IDC_STATIC_ENVERB_REVERBATTEN, m_kReverbAttenDisplay);
    DDX_Control(pDX, IDC_STATIC_ENVERB_REFLECTDELAY, m_kReflectDelayDisplay);
    DDX_Control(pDX, IDC_STATIC_ENVERB_REVERBDELAY, m_kReverbDelayDisplay);
    DDX_Control(pDX, IDC_STATIC_ENVERB_DECAYTIME, m_kDecayDisplay);
    DDX_Control(pDX, IDC_STATIC_ENVERB_HFRATIO, m_kDecayHFRatioDisplay);
    DDX_Control(pDX, IDC_STATIC_ENVERB_ROLLOFF, m_kRolloffDisplay);
    DDX_Control(pDX, IDC_STATIC_ENVERB_DIFFUSION, m_kDiffusionDisplay);
    DDX_Control(pDX, IDC_STATIC_ENVERB_DENSITY, m_kDensityDisplay);
    DDX_Control(pDX, IDC_STATIC_ENVERB_HFREF, m_kHFRefDisplay);
    DDX_Control(pDX, IDC_SLIDER_ENVERB_ROOMATTEN, m_kRoomAttenSlider);
    DDX_Control(pDX, IDC_SLIDER_ENVERB_HFATTEN, m_kHFAttenSlider);
    DDX_Control(pDX, IDC_SLIDER_ENVERB_REFLECTATTEN, m_kReflectAttenSlider);
    DDX_Control(pDX, IDC_SLIDER_ENVERB_REVERBATTEN, m_kReverbAttenSlider);
    DDX_Control(pDX, IDC_SLIDER_ENVERB_REFLECTDELAY, m_kReflectDelaySlider);
    DDX_Control(pDX, IDC_SLIDER_ENVERB_REVERBDELAY, m_kReverbDelaySlider);
    DDX_Control(pDX, IDC_SLIDER_ENVERB_DECAY, m_kDecaySlider);
    DDX_Control(pDX, IDC_SLIDER_ENVERB_DECAYHFRATIO, m_kDecayHFRatioSlider);
    DDX_Control(pDX, IDC_SLIDER_ENVERB_ROLLOFF, m_kRolloffSlider);
    DDX_Control(pDX, IDC_SLIDER_ENVERB_DIFFUSION, m_kDiffusionSlider);
    DDX_Control(pDX, IDC_SLIDER_ENVERB_DENSITY, m_kDensitySlider);
    DDX_Control(pDX, IDC_SLIDER_ENVERB_HFREF, m_kHFRefSlider);
}

BOOL CEnVerbPropertyPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();
    
    PopulatePresetComboBox();
    InitializeSliders();
    m_kPresetCombo.EnableWindow(FALSE);
    m_kCheckUsePreset.SetCheck(BST_UNCHECKED);

    return TRUE;
}

///////////////////////////////////////////////////////////

EnVerbEffect::PRESET CEnVerbPropertyPage::GetPreset ()
{
    EnVerbEffect::PRESET ePreset;

    if ( m_kCheckUsePreset.GetCheck() == BST_CHECKED )
        ePreset = (EnVerbEffect::PRESET)m_kPresetCombo.GetCurSel();
    else
        ePreset = EnVerbEffect::NONE;

    return ePreset;
}

void CEnVerbPropertyPage::GetPresetString(CString& rstrPreset, 
    EnVerbEffect::PRESET ePreset)
{
    m_kPresetCombo.GetLBText((int)ePreset,rstrPreset);
}

long CEnVerbPropertyPage::GetRoomAtten ()
{
    return (long)m_kRoomAttenSlider.GetPos();
}

long CEnVerbPropertyPage::GetHFAtten ()
{
    return (long)m_kHFAttenSlider.GetPos();
}

long CEnVerbPropertyPage::GetReflectAtten ()
{
    return (long)m_kReflectAttenSlider.GetPos();
}

long CEnVerbPropertyPage::GetReverbAtten ()
{
    return (long)m_kReverbAttenSlider.GetPos();
}

float CEnVerbPropertyPage::GetReflectDelay ()
{
    return m_kReflectDelaySlider.GetPos()/100.0f;
}

float CEnVerbPropertyPage::GetReverbDelay ()
{
    return m_kReverbDelaySlider.GetPos()/100.0f;
}

float CEnVerbPropertyPage::GetDecayTime ()
{
    return m_kDecaySlider.GetPos()/10.0f;
}

float CEnVerbPropertyPage::GetDecayTimeHFRatio ()
{
    return m_kDecayHFRatioSlider.GetPos()/10.0f;
}

float CEnVerbPropertyPage::GetRolloff ()
{
    return m_kRolloffSlider.GetPos()/10.0f;
}

float CEnVerbPropertyPage::GetDiffusion ()
{
    return (float)m_kDiffusionSlider.GetPos();
}

float CEnVerbPropertyPage::GetDensity ()
{
    return (float)m_kDensitySlider.GetPos();
}

float CEnVerbPropertyPage::GetHFRef ()
{
    return (float)m_kHFRefSlider.GetPos()/10.0f;
}

///////////////////////////////////////////////////////////

void CEnVerbPropertyPage::InitializeSliders ()
{
    int iMin, iMax;
    CString strValue;

    m_kRoomAttenSlider.SetRange((int)EnVerbEffect::MIN_ROOMATTEN,
        (int)EnVerbEffect::MAX_ROOMATTEN,TRUE);
    m_kRoomAttenSlider.GetRange(iMin,iMax);
    m_kRoomAttenSlider.SetTicFreq((iMax-iMin)/10);
    m_kRoomAttenSlider.SetPos(-100);
    strValue.Format(L"%d",-100);
    m_kRoomAttenDisplay.SetWindowText(strValue);

    m_kHFAttenSlider.SetRange((int)EnVerbEffect::MIN_ROOMHFATTEN,
        (int)EnVerbEffect::MAX_ROOMHFATTEN,TRUE);
    m_kHFAttenSlider.GetRange(iMin,iMax);
    m_kHFAttenSlider.SetTicFreq((iMax-iMin)/10);
    m_kHFAttenSlider.SetPos(-100);
    strValue.Format(L"%d",-100);
    m_kHFAttenDisplay.SetWindowText(strValue);

    m_kReflectAttenSlider.SetRange((int)EnVerbEffect::MIN_REFLECTATTEN,
        (int)EnVerbEffect::MAX_REFLECTATTEN,TRUE);
    m_kReflectAttenSlider.GetRange(iMin,iMax);
    m_kReflectAttenSlider.SetTicFreq((iMax-iMin)/10);
    m_kReflectAttenSlider.SetPos(-2600);
    strValue.Format(L"%d",-2600);
    m_kReflectAttenDisplay.SetWindowText(strValue);

    m_kReverbAttenSlider.SetRange((int)EnVerbEffect::MIN_REVERBATTEN,
        (int)EnVerbEffect::MAX_REVERBATTEN,TRUE);
    m_kReverbAttenSlider.GetRange(iMin,iMax);
    m_kReverbAttenSlider.SetTicFreq((iMax-iMin)/10);
    m_kReverbAttenSlider.SetPos(200);
    strValue.Format(L"%d",200);
    m_kReverbAttenDisplay.SetWindowText(strValue);

    m_kReflectDelaySlider.SetRange((int)(100.0f*EnVerbEffect::MIN_REFLECTDELAY),
        (int)(100.0f*EnVerbEffect::MAX_REFLECTDELAY),TRUE);
    m_kReflectDelaySlider.GetRange(iMin,iMax);
    m_kReflectDelaySlider.SetTicFreq((iMax-iMin)/10);
    m_kReflectDelaySlider.SetPos(1);
    strValue.Format(L"%.2f",0.01f);
    m_kReflectDelayDisplay.SetWindowText(strValue);

    m_kReverbDelaySlider.SetRange((int)(100.0f*EnVerbEffect::MIN_REVERBDELAY),
        (int)(100.0f*EnVerbEffect::MAX_REVERBDELAY),TRUE);
    m_kReverbDelaySlider.GetRange(iMin,iMax);
    m_kReverbDelaySlider.SetTicFreq((iMax-iMin)/10);
    m_kReverbDelaySlider.SetPos(1);
    strValue.Format(L"%.2f",0.01f);
    m_kReverbDelayDisplay.SetWindowText(strValue);

    m_kDecaySlider.SetRange((int)(10.0f*EnVerbEffect::MIN_DECAYTIME),
        (int)(10.0f*EnVerbEffect::MAX_DECAYTIME),TRUE);
    m_kDecaySlider.GetRange(iMin,iMax);
    m_kDecaySlider.SetTicFreq((iMax-iMin)/10);
    m_kDecaySlider.SetPos(15);
    strValue.Format(L"%.1f",1.5);
    m_kDecayDisplay.SetWindowText(strValue);

    m_kDecayHFRatioSlider.SetRange((int)(10.0f*EnVerbEffect::MIN_DECAYTIMEHFRATIO),
        (int)(10.0f*EnVerbEffect::MAX_DECAYTIMEHFRATIO),TRUE);
    m_kDecayHFRatioSlider.GetRange(iMin,iMax);
    m_kDecayHFRatioSlider.SetTicFreq((int)ceilf((iMax-iMin)/10.0f));
    m_kDecayHFRatioSlider.SetPos(8);
    strValue.Format(L"%.1f",0.8f);
    m_kDecayHFRatioDisplay.SetWindowText(strValue);

    m_kDecaySlider.SetRange((int)(10.0f*EnVerbEffect::MIN_DECAYTIME),
        (int)(10.0f*EnVerbEffect::MAX_DECAYTIME),TRUE);
    m_kDecaySlider.GetRange(iMin,iMax);
    m_kDecaySlider.SetTicFreq((iMax-iMin)/10);
    m_kDecaySlider.SetPos(15);
    strValue.Format(L"%.1f",1.5);
    m_kDecayDisplay.SetWindowText(strValue);

    m_kRolloffSlider.SetRange((int)(10.0f*EnVerbEffect::MIN_ROLLOFF),
        (int)(10.0f*EnVerbEffect::MAX_ROLLOFF),TRUE);
    m_kRolloffSlider.GetRange(iMin,iMax);
    m_kRolloffSlider.SetTicFreq((iMax-iMin)/10);
    m_kRolloffSlider.SetPos(0);
    strValue.Format(L"%.1f",0.0f);
    m_kRolloffDisplay.SetWindowText(strValue);

    m_kDiffusionSlider.SetRange((int)EnVerbEffect::MIN_DIFFUSION,
        (int)EnVerbEffect::MAX_DIFFUSION,TRUE);
    m_kDiffusionSlider.GetRange(iMin,iMax);
    m_kDiffusionSlider.SetTicFreq((iMax-iMin)/10);
    m_kDiffusionSlider.SetPos(100);
    strValue.Format(L"%d",100);
    m_kDiffusionDisplay.SetWindowText(strValue);

    m_kDensitySlider.SetRange((int)EnVerbEffect::MIN_DENSITY,
        (int)EnVerbEffect::MAX_DENSITY,TRUE);
    m_kDensitySlider.GetRange(iMin,iMax);
    m_kDensitySlider.SetTicFreq((iMax-iMin)/10);
    m_kDensitySlider.SetPos(100);
    strValue.Format(L"%d",100);
    m_kDensityDisplay.SetWindowText(strValue);

    m_kHFRefSlider.SetRange((int)(10.0f*EnVerbEffect::MIN_HFREF),
        (int)(10.0f*EnVerbEffect::MAX_HFREF),TRUE);
    m_kHFRefSlider.GetRange(iMin,iMax);
    m_kHFRefSlider.SetTicFreq((iMax-iMin)/10);
    m_kHFRefSlider.SetPos(50000);
    strValue.Format(L"%d",5000);
    m_kHFRefDisplay.SetWindowText(strValue);
}

void CEnVerbPropertyPage::PopulatePresetComboBox ()
{
    CString strPreset;

    strPreset.LoadString(IDS_ENVERBPRESET_ALLEY);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_ARENA);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_AUDITORIUM);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_BATHROOM);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_CAVE);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_CARPETEDHALLWAY);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_CITY);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_CONCERTHALL);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_DEFAULT);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_FOREST);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_GENERIC);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_HALLWAY);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_HANGAR);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_LARGEHALL);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_LARGEROOM);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_LIVINGROOM);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_MEDIUMHALL);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_MOUNTAINS);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_PADDEDCELL);
    m_kPresetCombo.AddString(strPreset);    
    strPreset.LoadString(IDS_ENVERBPRESET_PARKINGLOT);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_PLAIN);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_PLATE);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_QUARRY);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_ROOM);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_SEWERPIPE);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_SMALLROOM);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_STONECORRIDOR);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_STONEROOM);
    m_kPresetCombo.AddString(strPreset);
    strPreset.LoadString(IDS_ENVERBPRESET_UNDERWATER);
    m_kPresetCombo.AddString(strPreset);

    m_kPresetCombo.SetCurSel(0);
}

///////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CEnVerbPropertyPage, CPropertyPage)
    ON_BN_CLICKED(IDC_CHECK_ENVERB_USEPRESET, OnBnClickedCheckUsePreset)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()


void CEnVerbPropertyPage::OnBnClickedCheckUsePreset()
{
    if ( m_kCheckUsePreset.GetCheck() == BST_CHECKED )
        m_kPresetCombo.EnableWindow(TRUE);      
    else
        m_kPresetCombo.EnableWindow(FALSE);
}

void CEnVerbPropertyPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl* pkSlider = (CSliderCtrl*)pScrollBar;
    CString strValue;

    if ( pkSlider->m_hWnd == m_kRoomAttenSlider.m_hWnd )
    {
        strValue.Format(L"%d", m_kRoomAttenSlider.GetPos());
        m_kRoomAttenDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kHFAttenSlider.m_hWnd )
    {
        strValue.Format(L"%d", m_kHFAttenSlider.GetPos());
        m_kHFAttenDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kReflectAttenSlider.m_hWnd )
    {
        strValue.Format(L"%d", m_kReflectAttenSlider.GetPos());
        m_kReflectAttenDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kReverbAttenSlider.m_hWnd )
    {
        strValue.Format(L"%d", m_kReverbAttenSlider.GetPos());
        m_kReverbAttenDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kReflectDelaySlider.m_hWnd )
    {
        strValue.Format(L"%.2f", m_kReflectDelaySlider.GetPos()/100.0f);
        m_kReflectDelayDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kReverbDelaySlider.m_hWnd )
    {
        strValue.Format(L"%.2f", m_kReverbDelaySlider.GetPos()/100.0f);
        m_kReverbDelayDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kDecaySlider.m_hWnd )
    {
        strValue.Format(L"%.1f", m_kDecaySlider.GetPos()/10.0f);
        m_kDecayDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kDecayHFRatioSlider.m_hWnd )
    {
        strValue.Format(L"%.2f", m_kDecayHFRatioSlider.GetPos()/10.0f);
        m_kDecayHFRatioDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kRolloffSlider.m_hWnd )
    {
        strValue.Format(L"%.1f", m_kRolloffSlider.GetPos()/10.0f);
        m_kRolloffDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kDiffusionSlider.m_hWnd )
    {
        strValue.Format(L"%d", m_kDiffusionSlider.GetPos());
        m_kDiffusionDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kDensitySlider.m_hWnd )
    {
        strValue.Format(L"%d", m_kDensitySlider.GetPos());
        m_kDensityDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kHFRefSlider.m_hWnd )
    {
        strValue.Format(L"%d", m_kHFRefSlider.GetPos()/10);
        m_kHFRefDisplay.SetWindowText(strValue);
    }

    CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

