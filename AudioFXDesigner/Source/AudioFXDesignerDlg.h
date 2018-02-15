#pragma once

#include "afxwin.h"
#include <Mmreg.h>
#include "AmpModPropertyPage.h"
#include "ChorusPropertyPage.h"
#include "CompressorPropertyPage.h"
#include "DelayPropertyPage.h"
#include "DistortionPropertyPage.h"
#include "EnVerbPropertyPage.h"
#include "FlangerPropertyPage.h"
#include "ParamEQPropertyPage.h"
#include "ReverbPropertyPage.h"
#include "MAAudioRenderer.pkg"
#include "MADXSoundRenderer.h"

class CAudioFXDesignerDlg : public CDialog
{
public:
    CAudioFXDesignerDlg(CWnd* pParent = NULL);
    enum { IDD = IDD_AUDIOFXDESIGNER };

    void OnIdle (void);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    virtual void PostNcDestroy();

    void DeselectAllEffects (bool bDisable = false);

    void GetCurrentEffectSettings ();
    void GetAmpModSettings ();
    void GetChorusSettings ();
    void GetCompressorSettings ();
    void GetDelaySettings ();
    void GetDistortionSettings ();
    void GetEnVerbSettings ();
    void GetFlangerSettings ();
    void GetParamEQSettings ();
    void GetReverbSettings ();

    void SaveEffectParams (FILE* pkFile, MagicAudio::AmpModEffect* pkEffect);
    void SaveEffectParams (FILE* pkFile, MagicAudio::ChorusEffect* pkEffect);
    void SaveEffectParams (FILE* pkFile, MagicAudio::CompressorEffect* pkEffect);
    void SaveEffectParams (FILE* pkFile, MagicAudio::DelayEffect* pkEffect);
    void SaveEffectParams (FILE* pkFile, MagicAudio::DistortionEffect* pkEffect);
    void SaveEffectParams (FILE* pkFile, MagicAudio::FlangerEffect* pkEffect);
    void SaveEffectParams (FILE* pkFile, MagicAudio::ParametricEqEffect* pkEffect);
    void SaveEffectParams (FILE* pkFile, MagicAudio::EnVerbEffect* pkEffect);
    void SaveEffectParams (FILE* pkFile, MagicAudio::ReverbEffect* pkEffect);

    void UpdateUIOnStop ();
    void UpdateUIOnPlay ();

    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();

    afx_msg void OnBnClickedButtonLoad();
    afx_msg void OnBnClickedButtonPlay();
    afx_msg void OnBnClickedButtonSave();
    afx_msg void OnBnClickedButtonStop();

    afx_msg void OnBnClickedCheckAmpMod();
    afx_msg void OnBnClickedCheckChorus();
    afx_msg void OnBnClickedCheckCompressor();
    afx_msg void OnBnClickedCheckDelay();
    afx_msg void OnBnClickedCheckDistortion();
    afx_msg void OnBnClickedCheckEnVerb();
    afx_msg void OnBnClickedCheckFlanger();
    afx_msg void OnBnClickedCheckParamEq();
    afx_msg void OnBnClickedCheckReverb();
    afx_msg void OnClose();

    HICON m_hIcon; 
    CPropertySheet m_kPropSheet;

    CButton m_kLoadButton;
    CButton m_kPlayButton;
    CButton m_kStopButton;
    CButton m_kSaveButton;

    CButton m_kCheckAmpMod;
    CButton m_kCheckChorus;
    CButton m_kCheckCompressor;
    CButton m_kCheckDelay;
    CButton m_kCheckDistortion;
    CButton m_kCheckEnVerb;
    CButton m_kCheckFlanger;
    CButton m_kCheckReverb;
    CButton m_kCheckParamEQ;

    CAmpModPropertyPage m_kAmpModPage;
    CChorusPropertyPage m_kChorusPage;
    CCompressorPropertyPage m_kCompressorPage;
    CDelayPropertyPage m_kDelayPage;
    CDistortionPropertyPage m_kDistortionPage;
    CEnVerbPropertyPage m_kEnVerbPage;
    CFlangerPropertyPage m_kFlangerPage;
    CParamEQPropertyPage m_kParamEQPage;
    CReverbPropertyPage m_kReverbPage;

	MagicAudio::Pointer<MagicAudio::Audio> m_spkAudio;
    static MagicAudio::Pointer<MagicAudio::SoundRenderer> ms_spkSoundRenderer;
};
