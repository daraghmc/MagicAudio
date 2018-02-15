#include "stdafx.h"
#include "AudioFXDesigner.h"
#include "ParamEQPropertyPage.h"

using namespace MagicAudio;

IMPLEMENT_DYNAMIC(CParamEQPropertyPage, CPropertyPage)
CParamEQPropertyPage::CParamEQPropertyPage()
    : CPropertyPage(CParamEQPropertyPage::IDD)
{
}

CParamEQPropertyPage::~CParamEQPropertyPage()
{
}

void CParamEQPropertyPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER_PARAMEQ_GAIN, m_kGainSlider);
    DDX_Control(pDX, IDC_SLIDER_PARAMEQ_CENTER, m_kCenterSlider);
    DDX_Control(pDX, IDC_SLIDER_PARAMEQ_BANDWIDTH, m_kBandwidthSlider);
    DDX_Control(pDX, IDC_STATIC_PARAMEQ_GAIN, m_kGainDisplay);
    DDX_Control(pDX, IDC_STATIC_PARAMEQ_CENTER, m_kCenterDisplay);
    DDX_Control(pDX, IDC_STATIC_PARAMEQ_BANDWIDTH, m_kBandwidthDisplay);
}

BOOL CParamEQPropertyPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    int iMin, iMax;
    CString strValue;

    m_kGainSlider.SetRange((int)ParametricEqEffect::MIN_GAIN,
        (int)ParametricEqEffect::MAX_GAIN,TRUE);
    m_kGainSlider.GetRange(iMin,iMax);
    m_kGainSlider.SetTicFreq((iMax-iMin)/10);
    m_kGainSlider.SetPos(0);
    strValue.Format(L"%d",0);
    m_kGainDisplay.SetWindowText(strValue);

    m_kCenterSlider.SetRange((int)ParametricEqEffect::MIN_CENTER,
        (int)ParametricEqEffect::MAX_CENTER,TRUE);
    m_kCenterSlider.GetRange(iMin,iMax);
    m_kCenterSlider.SetTicFreq((iMax-iMin)/10);
    m_kCenterSlider.SetPos(8000);
    strValue.Format(L"%d",8000);
    m_kCenterDisplay.SetWindowText(strValue);

    m_kBandwidthSlider.SetRange((int)ParametricEqEffect::MIN_BANDWIDTH,
        (int)ParametricEqEffect::MAX_BANDWIDTH,TRUE);
    m_kBandwidthSlider.GetRange(iMin,iMax);
    m_kBandwidthSlider.SetTicFreq((iMax-iMin)/10);
    m_kBandwidthSlider.SetPos(12);
    strValue.Format(L"%d",12);
    m_kBandwidthDisplay.SetWindowText(strValue);

    return TRUE;
}

///////////////////////////////////////////////////////////

float CParamEQPropertyPage::GetGain ()
{
    return (float)m_kGainSlider.GetPos();
}

float CParamEQPropertyPage::GetCenter ()
{
    return (float)m_kCenterSlider.GetPos(); 
}

float CParamEQPropertyPage::GetBandwidth ()
{
    return (float)m_kBandwidthSlider.GetPos();
}

BEGIN_MESSAGE_MAP(CParamEQPropertyPage, CPropertyPage)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()

void CParamEQPropertyPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl* pkSlider = (CSliderCtrl*)pScrollBar;
    CString strValue;

    if ( pkSlider->m_hWnd == m_kGainSlider.m_hWnd )
    {
        strValue.Format(L"%d", m_kGainSlider.GetPos());
        m_kGainDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kCenterSlider.m_hWnd )
    {
        strValue.Format(L"%d", m_kCenterSlider.GetPos());
        m_kCenterDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kBandwidthSlider.m_hWnd )
    {
        strValue.Format(L"%d", m_kBandwidthSlider.GetPos());
        m_kBandwidthDisplay.SetWindowText(strValue);
    }

    CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}
