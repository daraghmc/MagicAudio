#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "MAAudioEffects.h"

class CDelayPropertyPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CDelayPropertyPage)

public:
    CDelayPropertyPage();
    virtual ~CDelayPropertyPage();
    enum { IDD = IDD_DELAY };

    float GetMix ();
    float GetFeedback ();
    float GetLeftDelay ();
    float GetRightDelay ();
    bool GetPan ();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    CSliderCtrl m_kMixSlider;
    CSliderCtrl m_kFeedbackSlider;
    CSliderCtrl m_kLeftDelaySlider;
    CSliderCtrl m_kRightDelaySlider;

    CStatic m_kMixDisplay;
    CStatic m_kFeedbackDisplay;
    CStatic m_kLeftDelayDisplay;
    CStatic m_kRightDelayDisplay;
    CButton m_kCheckPan;
};
