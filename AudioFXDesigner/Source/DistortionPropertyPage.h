#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "MAAudioEffects.h"

class CDistortionPropertyPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CDistortionPropertyPage)

public:
    CDistortionPropertyPage();
    virtual ~CDistortionPropertyPage();
    enum { IDD = IDD_DISTORTION };

    float GetGain ();
    float GetIntensity ();
    float GetCutoff ();
    float GetCenter ();
    float GetBandwidth ();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    CStatic m_kGainDisplay;
    CStatic m_kIntensityDisplay;
    CStatic m_kCenterDisplay;
    CStatic m_kBandwidthDisplay;
    CStatic m_kCutoffDisplay;
    CSliderCtrl m_kGainSlider;
    CSliderCtrl m_kIntensitySlider;
    CSliderCtrl m_kCenterSlider;
    CSliderCtrl m_kBandwidthSlider;
    CSliderCtrl m_kCutoffSlider;
};
