#pragma once

#include "MAAudioEffects.h"

class CChorusPropertyPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CChorusPropertyPage)

public:
    CChorusPropertyPage();
    virtual ~CChorusPropertyPage();
    enum { IDD = IDD_CHORUS };

    float GetMix ();
    float GetDepth ();
    float GetFrequency ();
    float GetDelay ();
    float GetFeedback ();
	MagicAudio::ChorusEffect::WAVEFORM GetWaveform ();
	MagicAudio::ChorusEffect::PHASE GetPhase ();

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
};
