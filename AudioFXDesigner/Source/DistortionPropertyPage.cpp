#include "stdafx.h"
#include "AudioFXDesigner.h"
#include "DistortionPropertyPage.h"

using namespace MagicAudio;

IMPLEMENT_DYNAMIC(CDistortionPropertyPage, CPropertyPage)
CDistortionPropertyPage::CDistortionPropertyPage()
    : CPropertyPage(CDistortionPropertyPage::IDD)
{
}

CDistortionPropertyPage::~CDistortionPropertyPage()
{
}

void CDistortionPropertyPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_DISTORT_GAIN, m_kGainDisplay);
    DDX_Control(pDX, IDC_STATIC_DISTORT_INTENSITY, m_kIntensityDisplay);
    DDX_Control(pDX, IDC_STATIC_DISTORT_CENTER, m_kCenterDisplay);
    DDX_Control(pDX, IDC_STATIC_DISTORT_BANDWIDTH, m_kBandwidthDisplay);
    DDX_Control(pDX, IDC_STATIC_DISTORT_CUTOFF, m_kCutoffDisplay);
    DDX_Control(pDX, IDC_SLIDER_DISTORT_GAIN, m_kGainSlider);
    DDX_Control(pDX, IDC_SLIDER_DISTORT_INTENSITY, m_kIntensitySlider);
    DDX_Control(pDX, IDC_SLIDER_DISTORT_CENTER, m_kCenterSlider);
    DDX_Control(pDX, IDC_SLIDER_DISTORT_BANDWIDTH, m_kBandwidthSlider);
    DDX_Control(pDX, IDC_SLIDER_DISTORT_CUTOFF, m_kCutoffSlider);
}

BOOL CDistortionPropertyPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    int iMin, iMax;
    CString strValue;

    m_kGainSlider.SetRange((int)DistortionEffect::MIN_GAIN,
        (int)DistortionEffect::MAX_GAIN,TRUE);
    m_kGainSlider.GetRange(iMin,iMax);
    m_kGainSlider.SetTicFreq((iMax-iMin)/10);
    m_kGainSlider.SetPos(-18);
    strValue.Format(L"%d",-18);
    m_kGainDisplay.SetWindowText(strValue);

    m_kBandwidthSlider.SetRange((int)DistortionEffect::MIN_BANDWIDTH,
        (int)DistortionEffect::MAX_BANDWIDTH,TRUE);
    m_kBandwidthSlider.GetRange(iMin,iMax);
    m_kBandwidthSlider.SetTicFreq((iMax-iMin)/10);
    m_kBandwidthSlider.SetPos(2400);
    strValue.Format(L"%d",2400);
    m_kBandwidthDisplay.SetWindowText(strValue);

    m_kIntensitySlider.SetRange((int)DistortionEffect::MIN_INTENSITY,
        (int)DistortionEffect::MAX_INTENSITY,TRUE);
    m_kIntensitySlider.GetRange(iMin,iMax);
    m_kIntensitySlider.SetTicFreq((iMax-iMin)/10);
    m_kIntensitySlider.SetPos(15);
    strValue.Format(L"%d",15);
    m_kIntensityDisplay.SetWindowText(strValue);

    m_kCenterSlider.SetRange((int)DistortionEffect::MIN_CENTER,
        (int)DistortionEffect::MAX_CENTER,TRUE);
    m_kCenterSlider.GetRange(iMin,iMax);
    m_kCenterSlider.SetTicFreq((iMax-iMin)/10);
    m_kCenterSlider.SetPos(2400);
    strValue.Format(L"%d",2400);
    m_kCenterDisplay.SetWindowText(strValue);

    m_kCutoffSlider.SetRange((int)DistortionEffect::MIN_CUTOFF,
        (int)DistortionEffect::MAX_CUTOFF,TRUE);
    m_kCutoffSlider.GetRange(iMin,iMax);
    m_kCutoffSlider.SetTicFreq((iMax-iMin)/10);
    m_kCutoffSlider.SetPos(8000);
    strValue.Format(L"%d",8000);
    m_kCutoffDisplay.SetWindowText(strValue);

    return TRUE;
}

///////////////////////////////////////////////////////////

float CDistortionPropertyPage::GetGain ()
{
    return (float)m_kGainSlider.GetPos();
}

float CDistortionPropertyPage::GetIntensity ()
{
    return (float)m_kIntensitySlider.GetPos();
}

float CDistortionPropertyPage::GetCenter ()
{
    return (float)m_kCenterSlider.GetPos();
}

float CDistortionPropertyPage::GetCutoff ()
{
    return (float)m_kCutoffSlider.GetPos();
}

float CDistortionPropertyPage::GetBandwidth ()
{
    return (float)m_kBandwidthSlider.GetPos();
}

///////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDistortionPropertyPage, CPropertyPage)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()

void CDistortionPropertyPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl* pkSlider = (CSliderCtrl*)pScrollBar;
    CString strValue;

    if ( pkSlider->m_hWnd == m_kGainSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kGainSlider.GetPos());
        m_kGainDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kIntensitySlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kIntensitySlider.GetPos());
        m_kIntensityDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kCenterSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kCenterSlider.GetPos());
        m_kCenterDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kCutoffSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kCutoffSlider.GetPos());
        m_kCutoffDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kBandwidthSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kBandwidthSlider.GetPos());
        m_kBandwidthDisplay.SetWindowText(strValue);
    }

    CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}