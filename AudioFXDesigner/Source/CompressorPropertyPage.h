#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "MAAudioEffects.h"

class CCompressorPropertyPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CCompressorPropertyPage)

public:
    CCompressorPropertyPage();
    virtual ~CCompressorPropertyPage();
    enum { IDD = IDD_COMPRESSOR };

    float GetGain ();
    float GetRatio ();
    float GetThreshold ();
    float GetAttack ();
    float GetRelease ();
    float GetDelay ();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    CSliderCtrl m_kGainSlider;
    CSliderCtrl m_kRatioSlider;
    CSliderCtrl m_kThresholdSlider;
    CSliderCtrl m_kAttackSlider;
    CSliderCtrl m_kReleaseSlider;
    CSliderCtrl m_kDelaySlider;
    CStatic m_kGainDisplay;
    CStatic m_kRatioDisplay;
    CStatic m_kThresholdDisplay;
    CStatic m_kAttackDisplay;
    CStatic m_kReleaseDisplay;
    CStatic m_kDelayDisplay;
};
