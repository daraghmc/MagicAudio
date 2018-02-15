#include "stdafx.h"
#include "AudioFXDesigner.h"
#include "ChorusPropertyPage.h"

using namespace MagicAudio;

IMPLEMENT_DYNAMIC(CChorusPropertyPage, CPropertyPage)
CChorusPropertyPage::CChorusPropertyPage()
    : CPropertyPage(CChorusPropertyPage::IDD)
{
}

CChorusPropertyPage::~CChorusPropertyPage()
{
}

void CChorusPropertyPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_SLIDER_CHORUS_MIX, m_kMixSlider);
    DDX_Control(pDX, IDC_SLIDER_CHORUS_FEEDBACK, m_kFeedbackSlider);
    DDX_Control(pDX, IDC_SLIDER_CHORUS_DELAY, m_kDelaySlider);
    DDX_Control(pDX, IDC_SLIDER_CHORUS_DEPTH, m_kDepthSlider);
    DDX_Control(pDX, IDC_SLIDER_CHORUS_FREQUENCY, m_kFrequencySlider);

    DDX_Control(pDX, IDC_STATIC_CHORUS_MIX, m_kMixDisplay);
    DDX_Control(pDX, IDC_STATIC_CHORUS_FEEDBACK, m_kFeedbackDisplay);
    DDX_Control(pDX, IDC_STATIC_CHORUS_DELAY, m_kDelayDisplay);
    DDX_Control(pDX, IDC_STATIC_CHORUS_DEPTH, m_kDepthDisplay);
    DDX_Control(pDX, IDC_STATIC_CHORUS_FREQUENCY, m_kFrequencyDisplay);     
}

BOOL CChorusPropertyPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();
    
    int iMin, iMax;
    CString strValue;

    m_kMixSlider.SetRange((int)ChorusEffect::MIN_MIX,
        (int)ChorusEffect::MAX_MIX,TRUE);
    m_kMixSlider.GetRange(iMin,iMax);
    m_kMixSlider.SetTicFreq((iMax-iMin)/10);
    m_kMixSlider.SetPos(50);
    strValue.Format(L"%d",50);
    m_kMixDisplay.SetWindowText(strValue);
   
    m_kFeedbackSlider.SetRange((int)ChorusEffect::MIN_FEEDBACK,
        (int)ChorusEffect::MAX_FEEDBACK,TRUE);
    m_kFeedbackSlider.GetRange(iMin,iMax);
    m_kFeedbackSlider.SetTicFreq((iMax-iMin)/10);
    m_kFeedbackSlider.SetPos(25);
    strValue.Format(L"%d",25);
    m_kFeedbackDisplay.SetWindowText(strValue);

    m_kDelaySlider.SetRange((int)ChorusEffect::MIN_DELAY,
        10*(int)ChorusEffect::MAX_DELAY,TRUE);
    m_kDelaySlider.GetRange(iMin,iMax);
    m_kDelaySlider.SetTicFreq((iMax-iMin)/10);
    m_kDelaySlider.SetPos(160);
    strValue.Format(L"%.1f",16.0f);
    m_kDelayDisplay.SetWindowText(strValue);

    m_kFrequencySlider.SetRange((int)ChorusEffect::MIN_FREQ,
        10*(int)ChorusEffect::MAX_FREQ,TRUE);
    m_kFrequencySlider.GetRange(iMin,iMax);
    m_kFrequencySlider.SetTicFreq((iMax-iMin)/10);
    m_kFrequencySlider.SetPos((int)11);
    strValue.Format(L"%.1f",1.1f);
    m_kFrequencyDisplay.SetWindowText(strValue);

    m_kDepthSlider.SetRange((int)ChorusEffect::MIN_DEPTH,
        (int)ChorusEffect::MAX_DEPTH,TRUE);
    m_kDepthSlider.GetRange(iMin,iMax);
    m_kDepthSlider.SetTicFreq((iMax-iMin)/10);
    m_kDepthSlider.SetPos(10);
    strValue.Format(L"%d",10);
    m_kDepthDisplay.SetWindowText(strValue);

    CheckRadioButton(IDC_RADIO_CHORUS_PHASENEG180,IDC_RADIO_CHORUS_PHASEPOS180,
        IDC_RADIO_CHORUS_PHASEPOS90);
    CheckRadioButton(IDC_RADIO_CHORUS_WAVESINE,IDC_RADIO_CHORUS_WAVETRIANGLE,
        IDC_RADIO_CHORUS_WAVESINE);

    return TRUE;  
}

///////////////////////////////////////////////////////////

float CChorusPropertyPage::GetMix ()
{
    return (float)m_kMixSlider.GetPos();
}

float CChorusPropertyPage::GetDepth ()
{
    return (float)m_kDepthSlider.GetPos();
}

float CChorusPropertyPage::GetFrequency ()
{
    return (m_kFrequencySlider.GetPos()/10.0f);
}

float CChorusPropertyPage::GetDelay ()
{
    return (m_kDelaySlider.GetPos()/10.0f);
}

float CChorusPropertyPage::GetFeedback ()
{
    return (float)m_kFeedbackSlider.GetPos();
}

ChorusEffect::WAVEFORM CChorusPropertyPage::GetWaveform ()
{
    int iWhich = GetCheckedRadioButton(IDC_RADIO_CHORUS_WAVESINE,
    IDC_RADIO_CHORUS_WAVETRIANGLE);
    
    ChorusEffect::WAVEFORM eWaveform;

    switch ( iWhich )
    {
    case IDC_RADIO_CHORUS_WAVESINE:
        eWaveform = ChorusEffect::SINE;
        break;
    case IDC_RADIO_CHORUS_WAVETRIANGLE:
        eWaveform = ChorusEffect::TRIANGLE;
        break;
    }

    return eWaveform;
}

ChorusEffect::PHASE CChorusPropertyPage::GetPhase ()
{
    int iWhich = GetCheckedRadioButton(IDC_RADIO_CHORUS_PHASENEG180,
    IDC_RADIO_CHORUS_PHASEPOS180);
    
    ChorusEffect::PHASE ePhase;

    switch ( iWhich )
    {
    case IDC_RADIO_CHORUS_PHASENEG180:
        ePhase = ChorusEffect::NEG_180;
        break;
    case IDC_RADIO_CHORUS_PHASENEG90:
        ePhase = ChorusEffect::NEG_90;
        break;
    case IDC_RADIO_CHORUS_PHASEZERO:
        ePhase = ChorusEffect::ZERO;
        break;
    case IDC_RADIO_CHORUS_PHASEPOS90:
        ePhase = ChorusEffect::POS_90;
        break;
    case IDC_RADIO_CHORUS_PHASEPOS180:
        ePhase = ChorusEffect::POS_180;
        break;
    };

    return ePhase;
}

///////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CChorusPropertyPage, CPropertyPage)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()


void CChorusPropertyPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl* pkSlider = (CSliderCtrl*)pScrollBar;
    CString strValue;

    if ( pkSlider->m_hWnd == m_kMixSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kMixSlider.GetPos());
        m_kMixDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kFeedbackSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kFeedbackSlider.GetPos());
        m_kFeedbackDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kDelaySlider.m_hWnd )
    {
        strValue.Format(L"%.1f",m_kDelaySlider.GetPos()/10.0f);
        m_kDelayDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kDepthSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kDepthSlider.GetPos());
        m_kDepthDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kFrequencySlider.m_hWnd )
    {
        strValue.Format(L"%.1f",m_kFrequencySlider.GetPos()/10.0f);
        m_kFrequencyDisplay.SetWindowText(strValue);
    }

    CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}


