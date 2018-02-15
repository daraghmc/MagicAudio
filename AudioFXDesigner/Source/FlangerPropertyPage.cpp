#include "stdafx.h"
#include "AudioFXDesigner.h"
#include "FlangerPropertyPage.h"

using namespace MagicAudio;

IMPLEMENT_DYNAMIC(CFlangerPropertyPage, CPropertyPage)
CFlangerPropertyPage::CFlangerPropertyPage()
    : CPropertyPage(CFlangerPropertyPage::IDD)
{
}

CFlangerPropertyPage::~CFlangerPropertyPage()
{
}

void CFlangerPropertyPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_SLIDER_FLANGER_MIX, m_kMixSlider);
    DDX_Control(pDX, IDC_SLIDER_FLANGER_FEEDBACK, m_kFeedbackSlider);
    DDX_Control(pDX, IDC_SLIDER_FLANGER_DELAY, m_kDelaySlider);
    DDX_Control(pDX, IDC_SLIDER_FLANGER_DEPTH, m_kDepthSlider);
    DDX_Control(pDX, IDC_SLIDER_FLANGER_FREQUENCY, m_kFrequencySlider);

    DDX_Control(pDX, IDC_STATIC_FLANGER_MIX, m_kMixDisplay);
    DDX_Control(pDX, IDC_STATIC_FLANGER_FEEDBACK, m_kFeedbackDisplay);
    DDX_Control(pDX, IDC_STATIC_FLANGER_DELAY, m_kDelayDisplay);
    DDX_Control(pDX, IDC_STATIC_FLANGER_DEPTH, m_kDepthDisplay);
    DDX_Control(pDX, IDC_STATIC_FLANGER_FREQUENCY, m_kFrequencyDisplay);
}

BOOL CFlangerPropertyPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();
    
    int iMin, iMax;
    CString strValue;

    m_kMixSlider.SetRange((int)FlangerEffect::MIN_MIX,
        (int)FlangerEffect::MAX_MIX,TRUE);
    m_kMixSlider.GetRange(iMin,iMax);
    m_kMixSlider.SetTicFreq((iMax-iMin)/10);
    m_kMixSlider.SetPos(50);
    strValue.Format(L"%d",50);
    m_kMixDisplay.SetWindowText(strValue);
   
    m_kFeedbackSlider.SetRange((int)FlangerEffect::MIN_FEEDBACK,
        (int)FlangerEffect::MAX_FEEDBACK,TRUE);
    m_kFeedbackSlider.GetRange(iMin,iMax);
    m_kFeedbackSlider.SetTicFreq((iMax-iMin)/10);
    m_kFeedbackSlider.SetPos(50);
    strValue.Format(L"%d",50);
    m_kFeedbackDisplay.SetWindowText(strValue);

    m_kDelaySlider.SetRange((int)FlangerEffect::MIN_DELAY,
        10*(int)FlangerEffect::MAX_DELAY,TRUE);
    m_kDelaySlider.GetRange(iMin,iMax);
    m_kDelaySlider.SetTicFreq((iMax-iMin)/10);
    m_kDelaySlider.SetPos(20);
    strValue.Format(L"%.1f",2.0f);
    m_kDelayDisplay.SetWindowText(strValue);

    m_kFrequencySlider.SetRange((int)FlangerEffect::MIN_FREQ,
        10*(int)FlangerEffect::MAX_FREQ,TRUE);
    m_kFrequencySlider.GetRange(iMin,iMax);
    m_kFrequencySlider.SetTicFreq((iMax-iMin)/10);
    m_kFrequencySlider.SetPos(11);
    strValue.Format(L"%.1f",1.1);
    m_kFrequencyDisplay.SetWindowText(strValue);

    m_kDepthSlider.SetRange((int)FlangerEffect::MIN_DEPTH,
        (int)FlangerEffect::MAX_DEPTH,TRUE);
    m_kDepthSlider.GetRange(iMin,iMax);
    m_kDepthSlider.SetTicFreq((iMax-iMin)/10);
    m_kDepthSlider.SetPos(10);
    strValue.Format(L"%d",10);
    m_kDepthDisplay.SetWindowText(strValue);

    CheckRadioButton(IDC_RADIO_FLANGER_PHASENEG180,IDC_RADIO_FLANGER_PHASEPOS180,
    IDC_RADIO_FLANGER_PHASEZERO);
    CheckRadioButton(IDC_RADIO_FLANGER_WAVESINE,IDC_RADIO_FLANGER_WAVETRIANGLE,
    IDC_RADIO_FLANGER_WAVESINE);

    return TRUE;  
}

///////////////////////////////////////////////////////////

float CFlangerPropertyPage::GetMix ()
{
    return (float)m_kMixSlider.GetPos();
}

float CFlangerPropertyPage::GetDepth ()
{
    return (float)m_kDepthSlider.GetPos();
}

float CFlangerPropertyPage::GetFrequency ()
{
    return (m_kFrequencySlider.GetPos() / 10.0f);
}

float CFlangerPropertyPage::GetDelay ()
{
    return (float)m_kDelaySlider.GetPos() / 10.0f;
}

float CFlangerPropertyPage::GetFeedback ()
{
    return (float)m_kFeedbackSlider.GetPos();
}

FlangerEffect::WAVEFORM CFlangerPropertyPage::GetWaveform ()
{
    int iWhich = GetCheckedRadioButton(IDC_RADIO_FLANGER_WAVESINE,
    IDC_RADIO_FLANGER_WAVETRIANGLE);
    
    FlangerEffect::WAVEFORM eWaveform;

    switch ( iWhich )
    {
    case IDC_RADIO_FLANGER_WAVESINE:
        eWaveform = FlangerEffect::SINE;
        break;
    case IDC_RADIO_FLANGER_WAVETRIANGLE:
        eWaveform = FlangerEffect::TRIANGLE;
        break;
    }

    return eWaveform;
}

FlangerEffect::PHASE CFlangerPropertyPage::GetPhase ()
{
    int iWhich = GetCheckedRadioButton(IDC_RADIO_FLANGER_PHASENEG180,
    IDC_RADIO_FLANGER_PHASEPOS180);
    
    FlangerEffect::PHASE ePhase;

    switch ( iWhich )
    {
    case IDC_RADIO_FLANGER_PHASENEG180:
        ePhase = FlangerEffect::NEG_180;
        break;
    case IDC_RADIO_FLANGER_PHASENEG90:
        ePhase = FlangerEffect::NEG_90;
        break;
    case IDC_RADIO_FLANGER_PHASEZERO:
        ePhase = FlangerEffect::ZERO;
        break;
    case IDC_RADIO_FLANGER_PHASEPOS90:
        ePhase = FlangerEffect::POS_90;
        break;
    case IDC_RADIO_FLANGER_PHASEPOS180:
        ePhase = FlangerEffect::POS_180;
        break;
    };

    return ePhase;
}

///////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CFlangerPropertyPage, CPropertyPage)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()

void CFlangerPropertyPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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
        strValue.Format(L"%0.1f",m_kDelaySlider.GetPos()/10.0f);
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
