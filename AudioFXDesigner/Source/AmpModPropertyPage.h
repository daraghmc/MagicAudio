#pragma once

#include "afxcmn.h"
#include "afxwin.h"

#include "MAAudioEffects.h"

class CAmpModPropertyPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CAmpModPropertyPage)

public:
    CAmpModPropertyPage();
    virtual ~CAmpModPropertyPage();
    enum { IDD = IDD_AMPMOD };

    int GetFrequency ();
    MagicAudio::AmpModEffect::WAVEFORM GetWaveform ();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    CSliderCtrl m_kFrequencySlider;
    CStatic m_kFrequencyDisplay;
};
