#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "MAAudioEffects.h"

class CReverbPropertyPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CReverbPropertyPage)

public:
    CReverbPropertyPage();
    virtual ~CReverbPropertyPage();
    enum { IDD = IDD_STDREVERB };

    float GetMix ();
    float GetGain ();
    float GetTime ();
    float GetHFRatio ();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    CSliderCtrl m_kMixSlider;
    CSliderCtrl m_kGainSlider;
    CSliderCtrl m_kTimeSlider;      
    CSliderCtrl m_kHFRatioSlider;   

    CStatic m_kMixDisplay;
    CStatic m_kGainDisplay;
    CStatic m_kTimeDisplay;
    CStatic m_kHFRatioDisplay;
};
