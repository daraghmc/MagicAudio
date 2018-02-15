#include "stdafx.h"
#include "AudioFXDesigner.h"
#include "AmpModPropertyPage.h"

using namespace MagicAudio;

IMPLEMENT_DYNAMIC(CAmpModPropertyPage, CPropertyPage)
CAmpModPropertyPage::CAmpModPropertyPage()
    : CPropertyPage(CAmpModPropertyPage::IDD)
{
}

CAmpModPropertyPage::~CAmpModPropertyPage()
{
}

void CAmpModPropertyPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER_AMPMOD_FREQUENCY, m_kFrequencySlider);
    DDX_Control(pDX, IDC_STATIC_FREQUENCY, m_kFrequencyDisplay);
}

BOOL CAmpModPropertyPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    int iMin, iMax;
    CString strValue;

    m_kFrequencySlider.SetRange((int)AmpModEffect::MIN_FREQ,
        (int)AmpModEffect::MAX_FREQ,TRUE);
    m_kFrequencySlider.GetRange(iMin,iMax);
    m_kFrequencySlider.SetTicFreq((iMax-iMin)/10);
    m_kFrequencySlider.SetPos(20);
    strValue.Format(L"%d",20);
    m_kFrequencyDisplay.SetWindowText(strValue);

    CheckRadioButton(IDC_RADIO_AMPMOD_WAVETRIANGLE,IDC_RADIO_AMPMOD_WAVESQUARE,
        IDC_RADIO_AMPMOD_WAVETRIANGLE);
   
    return TRUE;
}

///////////////////////////////////////////////////////////

int CAmpModPropertyPage::GetFrequency ()
{
    return m_kFrequencySlider.GetPos();
}

AmpModEffect::WAVEFORM CAmpModPropertyPage::GetWaveform ()
{
    int iWhich = GetCheckedRadioButton(IDC_RADIO_AMPMOD_WAVETRIANGLE,
        IDC_RADIO_AMPMOD_WAVESQUARE);
    
    AmpModEffect::WAVEFORM eWaveform;

    switch ( iWhich )
    {
    case IDC_RADIO_AMPMOD_WAVETRIANGLE:
        eWaveform = AmpModEffect::TRIANGLE;
        break;
    case IDC_RADIO_AMPMOD_WAVESQUARE:
        eWaveform = AmpModEffect::SQUARE;
        break;  
    }

    return eWaveform;
}

///////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CAmpModPropertyPage, CPropertyPage)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()

void CAmpModPropertyPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl* pkSlider = (CSliderCtrl*)pScrollBar;
    CString strValue;

    if ( pkSlider->m_hWnd == m_kFrequencySlider.m_hWnd )
    {
        strValue.Format(L"%d", m_kFrequencySlider.GetPos());
        m_kFrequencyDisplay.SetWindowText(strValue);
    }

    CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}
