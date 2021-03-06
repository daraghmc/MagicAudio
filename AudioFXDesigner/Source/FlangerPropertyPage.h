#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "MAAudioEffects.h"

class CFlangerPropertyPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CFlangerPropertyPage)

public:
    CFlangerPropertyPage();
    virtual ~CFlangerPropertyPage();
    enum { IDD = IDD_FLANGER };

    float GetMix ();
    float GetDepth ();
    float GetFrequency ();
    float GetDelay ();
    float GetFeedback ();
	MagicAudio::FlangerEffect::WAVEFORM GetWaveform ();
	MagicAudio::FlangerEffect::PHASE GetPhase ();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    CSliderCtrl m_kMixSlider;
    CSliderCtrl m_kDepthSlider;
    CSliderCtrl m_kFrequencySlider;
    CSliderCtrl m_kDelaySlider;
    CSliderCtrl m_kFeedbackSlider;

    CStatic m_kMixDisplay;
    CStatic m_kDepthDisplay;
    CStatic m_kFrequencyDisplay;
    CStatic m_kDelayDisplay;
    CStatic m_kFeedbackDisplay;
    CButton m_kRadioWaveform;
    CButton m_kRadioPhase;
};
