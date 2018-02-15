#include "stdafx.h"
#include "AudioFXDesigner.h"
#include "ReverbPropertyPage.h"

using namespace MagicAudio;

IMPLEMENT_DYNAMIC(CReverbPropertyPage, CPropertyPage)
CReverbPropertyPage::CReverbPropertyPage()
    : CPropertyPage(CReverbPropertyPage::IDD)
{
}

CReverbPropertyPage::~CReverbPropertyPage()
{
}

void CReverbPropertyPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER_REVERB_MIX, m_kMixSlider);
    DDX_Control(pDX, IDC_SLIDER_REVERB_GAIN, m_kGainSlider);
    DDX_Control(pDX, IDC_SLIDER_REVERB_TIME, m_kTimeSlider);
    DDX_Control(pDX, IDC_SLIDER_REVERB_HFRATIO, m_kHFRatioSlider);

    DDX_Control(pDX, IDC_STATIC_REVERB_MIX, m_kMixDisplay);
    DDX_Control(pDX, IDC_STATIC_REVERB_GAIN, m_kGainDisplay);
    DDX_Control(pDX, IDC_STATIC_REVERB_TIME, m_kTimeDisplay);
    DDX_Control(pDX, IDC_STATIC_REVERB_HFRATIO, m_kHFRatioDisplay);
}

BOOL CReverbPropertyPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    int iMin, iMax;
    CString strValue;

    m_kMixSlider.SetRange((int)ReverbEffect::MIN_MIX,
        (int)ReverbEffect::MAX_MIX,TRUE);
    m_kMixSlider.GetRange(iMin,iMax);
    m_kMixSlider.SetTicFreq((iMax-iMin)/10);
    m_kMixSlider.SetPos(100);
    strValue.Format(L"%d",100);
    m_kMixDisplay.SetWindowText(strValue);
   
    m_kGainSlider.SetRange((int)ReverbEffect::MIN_GAIN,
        (int)ReverbEffect::MAX_GAIN,TRUE);
    m_kGainSlider.GetRange(iMin,iMax);
    m_kGainSlider.SetTicFreq((iMax-iMin)/10);
    m_kGainSlider.SetPos(100);
    strValue.Format(L"%d",100);
    m_kGainDisplay.SetWindowText(strValue);

    m_kTimeSlider.SetRange((int)ReverbEffect::MIN_TIME,
        100*(int)ReverbEffect::MAX_TIME,TRUE);
    m_kTimeSlider.GetRange(iMin,iMax);
    m_kTimeSlider.SetTicFreq((iMax-iMin)/10);
    m_kTimeSlider.SetPos(100000);
    strValue.Format(L"%.2f",1000.0f);
    m_kTimeDisplay.SetWindowText(strValue);

    m_kHFRatioSlider.SetRange((int)(1000.0f*ReverbEffect::MIN_HFRATIO),
        100*(int)(1000.0f*ReverbEffect::MAX_HFRATIO),TRUE);
    m_kHFRatioSlider.GetRange(iMin,iMax);
    m_kHFRatioSlider.SetTicFreq((iMax-iMin)/10);
    m_kHFRatioSlider.SetPos(1);
    strValue.Format(L"%.3f",0.001f);
    m_kHFRatioDisplay.SetWindowText(strValue);

    return TRUE;
}

///////////////////////////////////////////////////////////

float CReverbPropertyPage::GetMix ()
{
    return (float)m_kMixSlider.GetPos();
}

float CReverbPropertyPage::GetGain ()
{
    return (float)m_kGainSlider.GetPos();
}

float CReverbPropertyPage::GetTime ()
{
    return (float)m_kTimeSlider.GetPos()/100.0f;
}

float CReverbPropertyPage::GetHFRatio ()
{
    return (float)m_kHFRatioSlider.GetPos()/1000.0f;
}

///////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CReverbPropertyPage, CPropertyPage)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()

void CReverbPropertyPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl* pkSlider = (CSliderCtrl*)pScrollBar;
    CString strValue;

    if ( pkSlider->m_hWnd == m_kMixSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kMixSlider.GetPos());
        m_kMixDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kGainSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kGainSlider.GetPos());
        m_kGainDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kTimeSlider.m_hWnd )
    {
        strValue.Format(L"%0.2f",m_kTimeSlider.GetPos()/100.0f);
        m_kTimeDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kHFRatioSlider.m_hWnd )
    {
        strValue.Format(L"%0.3f",m_kHFRatioSlider.GetPos()/1000.0f);
        m_kHFRatioDisplay.SetWindowText(strValue);
    }

    CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}
