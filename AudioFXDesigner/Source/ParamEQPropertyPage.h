#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "MAAudioEffects.h"

class CParamEQPropertyPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CParamEQPropertyPage)

public:
    CParamEQPropertyPage();
    virtual ~CParamEQPropertyPage();
    enum { IDD = IDD_PARAMEQ };

    float GetGain ();
    float GetCenter ();
    float GetBandwidth ();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    CSliderCtrl m_kGainSlider;
    CSliderCtrl m_kCenterSlider;
    CSliderCtrl m_kBandwidthSlider;
    CStatic m_kGainDisplay;
    CStatic m_kCenterDisplay;
    CStatic m_kBandwidthDisplay;
};
