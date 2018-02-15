#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "MAAudioEffects.h"

class CEnVerbPropertyPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CEnVerbPropertyPage)

public:
    CEnVerbPropertyPage();
    virtual ~CEnVerbPropertyPage();
    enum { IDD = IDD_ENVERB };

	MagicAudio::EnVerbEffect::PRESET GetPreset ();
    void GetPresetString(CString& rstrPreset, MagicAudio::EnVerbEffect::PRESET ePreset);
    long GetRoomAtten ();
    long GetHFAtten ();
    long GetReflectAtten ();
    long GetReverbAtten ();
    float GetReflectDelay ();
    float GetReverbDelay ();
    float GetDecayTime ();
    float GetDecayTimeHFRatio ();
    float GetRolloff ();
    float GetDiffusion ();
    float GetDensity ();
    float GetHFRef ();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    void InitializeSliders (void);
    void PopulatePresetComboBox ();

    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedCheckUsePreset();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    
    CComboBox m_kPresetCombo;
    CButton m_kCheckUsePreset;

    CStatic m_kRoomAttenDisplay;
    CStatic m_kHFAttenDisplay;
    CStatic m_kReflectAttenDisplay;
    CStatic m_kReverbAttenDisplay;
    CStatic m_kReflectDelayDisplay;
    CStatic m_kReverbDelayDisplay;
    CStatic m_kDecayDisplay;
    CStatic m_kDecayHFRatioDisplay;
    CStatic m_kRolloffDisplay;
    CStatic m_kDiffusionDisplay;
    CStatic m_kDensityDisplay;
    CStatic m_kHFRefDisplay;

    CSliderCtrl m_kRoomAttenSlider;
    CSliderCtrl m_kHFAttenSlider;
    CSliderCtrl m_kReflectAttenSlider;
    CSliderCtrl m_kReverbAttenSlider;
    CSliderCtrl m_kReflectDelaySlider;
    CSliderCtrl m_kReverbDelaySlider;
    CSliderCtrl m_kDecaySlider;
    CSliderCtrl m_kDecayHFRatioSlider;
    CSliderCtrl m_kRolloffSlider;
    CSliderCtrl m_kDiffusionSlider;
    CSliderCtrl m_kDensitySlider;
    CSliderCtrl m_kHFRefSlider;
};
