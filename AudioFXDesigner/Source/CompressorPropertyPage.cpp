#include "stdafx.h"
#include "AudioFXDesigner.h"
#include "CompressorPropertyPage.h"

using namespace MagicAudio;

IMPLEMENT_DYNAMIC(CCompressorPropertyPage, CPropertyPage)
CCompressorPropertyPage::CCompressorPropertyPage()
    : CPropertyPage(CCompressorPropertyPage::IDD)
{
}

CCompressorPropertyPage::~CCompressorPropertyPage()
{
}

void CCompressorPropertyPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER_COMPRESSOR_GAIN, m_kGainSlider);
    DDX_Control(pDX, IDC_SLIDER_COMPRESSOR_RATIO, m_kRatioSlider);
    DDX_Control(pDX, IDC_SLIDER_COMPRESSOR_THRESHOLD, m_kThresholdSlider);
    DDX_Control(pDX, IDC_SLIDER_COMPRESSOR_ATTACK, m_kAttackSlider);
    DDX_Control(pDX, IDC_SLIDER_COMPRESSOR_RELEASE, m_kReleaseSlider);
    DDX_Control(pDX, IDC_SLIDER_COMPRESSOR_DELAY, m_kDelaySlider);
    DDX_Control(pDX, IDC_STATIC_COMPRESS_GAIN, m_kGainDisplay);
    DDX_Control(pDX, IDC_STATIC_COMPRESS_RATIO, m_kRatioDisplay);
    DDX_Control(pDX, IDC_STATIC_COMPRESS_THRESHOLD, m_kThresholdDisplay);
    DDX_Control(pDX, IDC_STATIC_COMPRESS_ATTACK, m_kAttackDisplay);
    DDX_Control(pDX, IDC_STATIC_COMPRESS_RELEASE, m_kReleaseDisplay);
    DDX_Control(pDX, IDC_STATIC_COMPRESS_DELAY, m_kDelayDisplay);
}

BOOL CCompressorPropertyPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    int iMin, iMax;
    CString strValue;

    m_kGainSlider.SetRange((int)CompressorEffect::MIN_GAIN,
        (int)CompressorEffect::MAX_GAIN,TRUE);
    m_kGainSlider.GetRange(iMin,iMax);
    m_kGainSlider.SetTicFreq((iMax-iMin)/10);
    m_kGainSlider.SetPos(0);
    strValue.Format(L"%d",0);
    m_kGainDisplay.SetWindowText(strValue);

    m_kRatioSlider.SetRange((int)CompressorEffect::MIN_RATIO,
        (int)CompressorEffect::MAX_RATIO,TRUE);
    m_kRatioSlider.GetRange(iMin,iMax);
    m_kRatioSlider.SetTicFreq((iMax-iMin)/10);
    m_kRatioSlider.SetPos(3);
    strValue.Format(L"%d",3);
    m_kRatioDisplay.SetWindowText(strValue);

    m_kAttackSlider.SetRange(10*(int)CompressorEffect::MIN_ATTACK,
        10*(int)CompressorEffect::MAX_ATTACK,TRUE);
    m_kAttackSlider.GetRange(iMin,iMax);
    m_kAttackSlider.SetTicFreq((iMax-iMin)/10);
    m_kAttackSlider.SetPos(100);
    strValue.Format(L"%.1f",10.0f);
    m_kAttackDisplay.SetWindowText(strValue);

    m_kReleaseSlider.SetRange((int)CompressorEffect::MIN_RELEASE,
        (int)CompressorEffect::MAX_RELEASE,TRUE);
    m_kReleaseSlider.GetRange(iMin,iMax);
    m_kReleaseSlider.SetTicFreq((iMax-iMin)/10);
    m_kReleaseSlider.SetPos(200);
    strValue.Format(L"%d",200);
    m_kReleaseDisplay.SetWindowText(strValue);

    m_kDelaySlider.SetRange(10*(int)CompressorEffect::MIN_DELAY,
        10*(int)CompressorEffect::MAX_DELAY,TRUE);
    m_kDelaySlider.GetRange(iMin,iMax);
    m_kDelaySlider.SetTicFreq((iMax-iMin)/10);
    m_kDelaySlider.SetPos(40);
    strValue.Format(L"%.1f",4.0f);
    m_kDelayDisplay.SetWindowText(strValue);

    m_kThresholdSlider.SetRange((int)CompressorEffect::MIN_THRESHOLD,
        (int)CompressorEffect::MAX_THRESHOLD,TRUE);
    m_kThresholdSlider.GetRange(iMin,iMax);
    m_kThresholdSlider.SetTicFreq((iMax-iMin)/10);
    m_kThresholdSlider.SetPos(-20);
    strValue.Format(L"%d",-20);
    m_kThresholdDisplay.SetWindowText(strValue);

    return TRUE;
}

///////////////////////////////////////////////////////////

float CCompressorPropertyPage::GetGain ()
{
    return (float)m_kGainSlider.GetPos();
}

float CCompressorPropertyPage::GetRatio ()
{
    return (float)m_kRatioSlider.GetPos();
}

float CCompressorPropertyPage::GetAttack ()
{
    return (float)m_kAttackSlider.GetPos()/10.0f;
}

float CCompressorPropertyPage::GetRelease ()
{
    return (float)m_kReleaseSlider.GetPos();
}

float CCompressorPropertyPage::GetDelay ()
{
    return (float)m_kDelaySlider.GetPos()/10.0f;
}

float CCompressorPropertyPage::GetThreshold ()
{
    return (float)m_kThresholdSlider.GetPos();
}

///////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CCompressorPropertyPage, CPropertyPage)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()

void CCompressorPropertyPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl* pkSlider = (CSliderCtrl*)pScrollBar;
    CString strValue;

    if ( pkSlider->m_hWnd == m_kGainSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kGainSlider.GetPos());
        m_kGainDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kRatioSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kRatioSlider.GetPos());
        m_kRatioDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kAttackSlider.m_hWnd )
    {
        strValue.Format(L"%.1f",m_kAttackSlider.GetPos()/10.0f);
        m_kAttackDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kReleaseSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kReleaseSlider.GetPos());
        m_kReleaseDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kDelaySlider.m_hWnd )
    {
        strValue.Format(L"%.1f",m_kDelaySlider.GetPos()/10.0f);
        m_kDelayDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kThresholdSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kThresholdSlider.GetPos());
        m_kThresholdDisplay.SetWindowText(strValue);
    }

    CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}
